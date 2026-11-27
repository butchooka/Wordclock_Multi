#!/usr/bin/env python3
"""
make_video.py - Wordclock 16x16, MP4 video of all fronts for MakerWorld

Converts the animated GIFs docs/render/Wordclock_Render_ALL_<hhmm>.gif (light) and
docs/render_dark/Wordclock_Render_ALL_<hhmm>.gif (dark) of tools/render_fronts.py into MP4 videos
(H.264, yuv420p, faststart) in makerworld/:
    makerworld/Wordclock_Render_ALL_<hhmm>.mp4, makerworld/Wordclock_Render_ALL_<hhmm>_dark.mp4
MakerWorld accepts videos up to 30 s, so the display time per front is limited: every front gets the same
time, at most the time of the GIF (1 s) and short enough that the whole video stays <= --max-s (29.5 s).
Unchanged videos (MP4 newer than its GIF) are skipped, --force or WC_FORCE=1 builds them again.
Needs ffmpeg on the PATH (winget install Gyan.FFmpeg) or the Python package imageio-ffmpeg, and Pillow.
Usage:  python3 tools/make_video.py [--max-s 29.5] [--fps 30] [--size 0] [--crf 18] [--force]
Called by tools/wordclock_tools.bat (action 5, after the renders).
"""
import argparse
import glob
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT = os.path.join(ROOT, "makerworld")
SETS = (("render", ""), ("render_dark", "_dark"))

try:
    from PIL import Image, ImageSequence
except ImportError:
    sys.exit("Pillow missing: python -m pip install --user pillow")


def ffmpeg_exe():
    exe = shutil.which("ffmpeg")
    if exe:
        return exe
    try:
        import imageio_ffmpeg
        return imageio_ffmpeg.get_ffmpeg_exe()
    except Exception:
        return None


def find_gif(folder):
    """Wordclock_Render_ALL_<hhmm>.gif (normal set, not _full) - the newest when there are several."""
    fs = [f for f in glob.glob(os.path.join(ROOT, "docs", folder, "Wordclock_Render_ALL_*.gif"))
          if re.search(r"_ALL_\d{4}\.gif$", f)]
    return max(fs, key=os.path.getmtime) if fs else None


def frames_of(gif):
    im = Image.open(gif)
    fr, ms = [], []
    for f in ImageSequence.Iterator(im):
        fr.append(f.convert("RGB"))
        ms.append(f.info.get("duration", im.info.get("duration", 1000)) or 1000)
    return fr, ms


def make(gif, mp4, a, exe):
    frames, ms = frames_of(gif)
    n = len(frames)
    gif_ms = max(ms)
    # same number of video frames per front, whole video <= max-s and no front longer than in the GIF
    k = min(int(a.max_s * a.fps) // n, max(1, round(gif_ms / 1000 * a.fps)))
    if k < 1:
        sys.exit("ERROR: %d fronts do not fit into %.1f s at %d fps" % (n, a.max_s, a.fps))
    w, h = frames[0].size
    if a.size:
        h = round(h * a.size / w)
        w = a.size
    w, h = w - w % 2, h - h % 2           # yuv420p needs even sizes
    tmp = mp4 + ".part.mp4"
    cmd = [exe, "-y", "-loglevel", "error", "-f", "rawvideo", "-pix_fmt", "rgb24", "-s", "%dx%d" % (w, h),
           "-r", str(a.fps), "-i", "-", "-c:v", "libx264", "-preset", "veryfast", "-crf", str(a.crf),
           "-pix_fmt", "yuv420p", "-movflags", "+faststart", "-an", tmp]
    p = subprocess.Popen(cmd, stdin=subprocess.PIPE)
    try:
        for f in frames:
            if f.size != (w, h):
                f = f.resize((w, h), Image.LANCZOS) if a.size else f.crop((0, 0, w, h))
            b = f.tobytes()
            for _ in range(k):
                p.stdin.write(b)
        p.stdin.close()
    except BrokenPipeError:
        pass
    if p.wait() != 0:
        if os.path.exists(tmp):
            os.remove(tmp)
        sys.exit("ERROR: ffmpeg failed for " + os.path.relpath(gif, ROOT))
    os.replace(tmp, mp4)
    print("video     ->  %s  (%d fronts, %d ms each, %.1f s, %dx%d)"
          % (os.path.relpath(mp4, ROOT), n, round(k * 1000 / a.fps), n * k / a.fps, w, h))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--max-s", type=float, default=29.5, help="maximum length of the video in seconds")
    ap.add_argument("--fps", type=int, default=30)
    ap.add_argument("--size", type=int, default=0, help="width of the video in pixels (0 = as the GIF)")
    ap.add_argument("--crf", type=int, default=18, help="H.264 quality (lower = better, default 18)")
    ap.add_argument("--force", action="store_true", help="build again even when unchanged")
    a = ap.parse_args()
    force = a.force or os.environ.get("WC_FORCE") == "1"
    exe = ffmpeg_exe()
    if not exe:
        print("skipped: ffmpeg not found - install it with:  winget install Gyan.FFmpeg  (then open a new console)")
        return 0
    if not os.path.isdir(OUT):
        os.makedirs(OUT)
    for folder, suf in SETS:
        gif = find_gif(folder)
        if not gif:
            print("skipped: no Wordclock_Render_ALL_<hhmm>.gif in docs/%s (run action 5 first)" % folder)
            continue
        base = os.path.splitext(os.path.basename(gif))[0]
        mp4 = os.path.join(OUT, base + suf + ".mp4")
        # old videos of another time
        for old in glob.glob(os.path.join(OUT, "Wordclock_Render_ALL_*%s.mp4" % suf)):
            if old != mp4 and re.search(r"_ALL_\d{4}%s\.mp4$" % suf, old):
                os.remove(old)
        if not force and os.path.exists(mp4) and os.path.getmtime(mp4) >= os.path.getmtime(gif):
            print("unchanged ->  " + os.path.relpath(mp4, ROOT))
            continue
        make(gif, mp4, a, exe)
    return 0


if __name__ == "__main__":
    sys.exit(main())
