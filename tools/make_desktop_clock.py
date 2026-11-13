#!/usr/bin/env python3
"""
make_desktop_clock.py - Wordclock 16x16, static desktop word clock (easter egg), v1.0

Compiles a tiny dumper (g++) per language from arduino/Wordclock/src/wc_lang_XX.h, collects the time text of
every minute of the day (like the header of the web interface, one line per grid row) and writes docs/wordclock_desktop.html:
one self-contained HTML file, system time + system language, no server, no internet.
    python3 tools/make_desktop_clock.py
"""
import glob, json, os, re, shutil, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "arduino", "Wordclock", "src")
OUT = os.path.join(ROOT, "docs", "wordclock_desktop.html")
CJK = re.compile("[\u3040-\u30ff\u3400-\u9fff\uac00-\ud7af]")

DUMPER = r'''
#include <cstdio>
#include <cstring>
#include "wc_core.h"
#include "wc_text.h"
#include LANG_FILE
int main(){
  char t[256], buf[64];
  wc_json_get(WC_LANG.ui_json,"html_lang",buf,sizeof(buf));
  printf("L\t%s\t%s\t%s\n",WC_LANG.code,WC_LANG.name,buf);
  for(int r=0;r<WC_ROWS;r++)printf("G\t%s\n",WC_LANG.grid[r]);
  for(int s=0;s<2;s++)for(int h=0;h<24;h++)for(int m=0;m<60;m++){
    int8_t cell[WC_N], wid[WC_N];
    memset(cell,-1,sizeof cell); memset(wid,-1,sizeof wid); t[0]=0;
    WcMark mk = {cell, 0, WC_LANG.grid, t, sizeof t, 0, wid, 0};
    WC_LANG.time_words(true,h,m,s,mk);
    printf("%d\t%d\t%d\t%s\t",s,h,m,t);
    // per word: its runs of lit cells "row:col:len" (a glued word can have several runs on different rows)
    for(int w=0;w<mk.widx;w++){printf(w?",":"");int k=0;
      for(int i=0;i<WC_N;i++)if(wid[i]==w&&(i%WC_COLS==0||wid[i-1]!=w)){int n=0;while(i%WC_COLS+n<WC_COLS&&wid[i+n]==w)n++;
        printf(k++?";%d:%d:%d":"%d:%d:%d",i/WC_COLS,i%WC_COLS,n);}}
    printf("\n");}
}
'''


def dump(cxx, tmp, lang):
    cpp = os.path.join(tmp, "dump.cpp")
    with open(cpp, "w", encoding="utf-8") as f:
        f.write(DUMPER)
    exe = os.path.join(tmp, "dump_" + lang + (".exe" if os.name == "nt" else ""))
    subprocess.run([cxx, "-std=c++11", "-w", "-I", SRC, '-DLANG_FILE="wc_lang_%s.h"' % lang, cpp, "-o", exe], check=True)
    out = subprocess.run([exe], check=True, capture_output=True).stdout.decode("utf-8")
    d, meta, grid = {}, None, []
    for line in out.splitlines():
        p = line.split("\t")
        if p[0] == "L": meta = p[1:]
        elif p[0] == "G": grid.append(p[1])
        else:
            words, runs = p[3].split(" "), p[4].split(",") if p[4] else []
            assert len(words) == len(runs), (lang, line)
            pieces = []                        # (grid row, text) in reading order
            for w, rs in zip(words, runs):
                rs = [tuple(map(int, r.split(":"))) for r in rs.split(";")]
                if len(rs) == 1 or not CJK.search(w):   # Latin etc.: a glued word stays together (row of its start)
                    pieces.append((min(rs, key=lambda r: (w.find(grid[r[0]][r[1]:r[1] + r[2]]), r))[0], w, True)); continue
                # CJK word glued over several runs: find the order of the runs that spells it, break by grid row
                k, first = 0, True
                while k < len(w):
                    hit = max((r for r in rs if w.startswith(grid[r[0]][r[1]:r[1] + r[2]], k)), key=lambda r: r[2], default=None)
                    assert hit, (lang, line)
                    pieces.append((hit[0], grid[hit[0]][hit[1]:hit[1] + hit[2]], first)); first = False
                    k += hit[2]; rs.remove(hit)
            lines = []                         # line break wherever the grid row changes
            for r, t, sp in pieces:
                if lines and lines[-1][0] == r: lines[-1][1] += (" " if sp else "") + t
                else: lines.append([r, t])
            d[(int(p[0]), int(p[1]), int(p[2]))] = "|".join(t for _, t in lines)
    return meta, d


def encode(meta, d):
    base = [d[(0, h, m)] for h in range(24) for m in range(60)]
    suf = []
    for k in range(1, 5):                      # "+ n MINUTES" is appended to the text without single minutes
        a, b = d[(0, 0, k)], d[(1, 0, k)]
        assert b.startswith(a), meta[0]
        assert b[len(a)] == "|", meta[0]     # "+ n MINUTES" always is a line of its own
        suf.append(b[len(a) + 1:])
    for h in range(24):
        for m in range(60):
            assert d[(1, h, m)] == d[(0, h, m)] + ("|" + suf[m % 5 - 1] if m % 5 else ""), (meta[0], h, m)
    h12 = base[:720] == base[720:]
    if h12: base = base[:720]
    words, wi, phr, pi, idx = [], {}, [], {}, []
    for t in base:
        if t not in pi:
            pi[t] = len(phr)
            ls = []
            for line in t.split("|"):
                ws = []
                for w in line.split(" "):
                    if w not in wi: wi[w] = len(words); words.append(w)
                    ws.append(wi[w])
                ls.append(".".join(map(str, ws)))
            phr.append("|".join(ls))
        idx.append(pi[t])
    rle = []
    for v in idx:
        if rle and rle[-1][0] == v: rle[-1][1] += 1
        else: rle.append([v, 1])
    return {"n": meta[1], "hl": meta[2], "w": words, "p": ",".join(phr),
            "i": ",".join(str(v) if c == 1 else "%d*%d" % (v, c) for v, c in rle), "s": suf}


TEMPLATE = r'''<!DOCTYPE html>
<!--
  wordclock_desktop.html - Wordclock 16x16, static desktop word clock (easter egg), v1.0
  GENERATED by tools/make_desktop_clock.py from arduino/Wordclock/src/wc_lang_XX.h - do not edit.
  Time in words like the header of the web interface, one line per row of the clock grid.
  System time, system language (browser). Gear (top right, shown on mouse move): single minutes, colour, size.
  Parameters (override the saved settings, e.g. for an iframe):
    ?lang=DE (code, e.g. GB, dialect_CH, scifi_TLH)  &min=0 (no "+ n MINUTES")  &color=ffb35c
    &size=48 (px, 0 = fit to the window)  &bg=transparent | 000000  &gear=0 (no gear)
  Keys: <- -> switch language.   https://github.com/butchooka/Wordclock_Multi
-->
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Wordclock</title>
<style>
html,body{height:100%;margin:0}
body{background:#0f0e0c;display:flex;align-items:center;justify-content:center;overflow:hidden;
     font:14px/1.4 system-ui,-apple-system,"Segoe UI",Roboto,sans-serif;color:#d8d0c4}
#w{font:600 20px/1.35 ui-monospace,"SF Mono",Menlo,Consolas,monospace;letter-spacing:.18em;color:#ffb35c;
   text-shadow:0 0 .5em rgba(255,170,80,.55);text-align:center}
#w div{white-space:nowrap}
#g{position:fixed;top:10px;right:10px;width:30px;height:30px;border:0;border-radius:50%;background:rgba(36,33,29,.75);
   color:#d8d0c4;font-size:18px;line-height:30px;padding:0;cursor:pointer;opacity:0;transition:opacity .4s}
#g.on,#g:focus-visible,body.open #g{opacity:.85}
#s{position:fixed;top:48px;right:10px;background:#1c1a17;border:1px solid #302c27;border-radius:12px;padding:12px 14px;
   min-width:230px;box-shadow:0 6px 24px rgba(0,0,0,.5);display:none}
body.open #s{display:block}
#s label{display:flex;align-items:center;justify-content:space-between;gap:12px;padding:5px 0}
#s input{accent-color:#c9721e}
#s input[type=range]{width:110px}
#s input[type=color]{width:42px;height:26px;border:0;padding:0;background:none}
#s .u{margin-top:8px;font-size:12px;color:#a59d90;word-break:break-all;user-select:all}
#s button{background:#24211d;color:#d8d0c4;border:1px solid #302c27;border-radius:8px;padding:3px 10px;cursor:pointer}
#n{position:fixed;left:12px;bottom:10px;color:#a59d90;opacity:0;transition:opacity .6s}
</style>
</head>
<body>
<div id="w"></div>
<button id="g" title="Settings" aria-label="Settings">&#9881;</button>
<div id="s">
  <label><span data-t="min">Single minutes</span><input type="checkbox" id="sMin"></label>
  <label><span data-t="col">Letter colour</span><span><input type="color" id="sCol"> <button id="sRes" title="Reset">&#8634;</button></span></label>
  <label><span data-t="size">Size</span><input type="range" id="sSize" min="0" max="200" step="2"></label>
  <div style="text-align:right;color:#a59d90;font-size:12px" id="sSizeV"></div>
  <div class="u" id="sUrl"></div>
</div>
<div id="n"></div>
<script>
const D=__DATA__;
const DEF={min:true,color:'#ffb35c',size:0};
const P=new URLSearchParams(location.search),C=Object.keys(D),$=id=>document.getElementById(id);
const E=$('w'),nav=(navigator.languages&&navigator.languages.length?navigator.languages:[navigator.language||'en']).map(s=>s.toLowerCase());
const UI=nav[0].startsWith('de')?{min:'Einzelminuten',col:'Farbe Buchstaben',size:'Größe',auto:'automatisch',link:'Link zum Einbinden'}
                                  :{min:'Single minutes',col:'Letter colour',size:'Size',auto:'fit to window',link:'Link for embedding'};
document.querySelectorAll('[data-t]').forEach(e=>e.textContent=UI[e.dataset.t]);
// settings: saved (per browser) < URL parameters
let S=Object.assign({},DEF);
try{Object.assign(S,JSON.parse(localStorage.getItem('wordclock_desktop')||'{}'));}catch(e){}
const hex=v=>/^[0-9a-f]{3}([0-9a-f]{3})?$/i.test(v)?'#'+v:v;
if(P.has('min'))S.min=P.get('min')!=='0';
if(P.has('color'))S.color=hex(P.get('color'));
if(P.has('size'))S.size=Math.max(0,parseInt(P.get('size'))||0);
if(P.get('bg'))document.body.style.background=hex(P.get('bg'));
if(P.get('gear')==='0')$('g').style.display='none';
function save(){try{localStorage.setItem('wordclock_desktop',JSON.stringify(S));}catch(e){}}

function pick(){
  const q=(P.get('lang')||'').toLowerCase(),k=C.find(c=>c.toLowerCase()===q);if(k)return k;
  for(const n of nav){const x=C.find(c=>D[c].hl.toLowerCase()===n);if(x)return x;
    const y=C.find(c=>D[c].hl.toLowerCase().split('-')[0]===n.split('-')[0]);if(y)return y;}
  return D.GB?'GB':C[0];
}
const cache={};
function lang(c){
  if(cache[c])return cache[c];
  const L=D[c],ph=L.p.split(',').map(p=>p.split('|').map(l=>l.split('.').map(i=>L.w[+i]).join(' '))),idx=[];
  for(const r of L.i.split(',')){const [v,n]=r.split('*');for(let j=0;j<(n?+n:1);j++)idx.push(+v);}
  return cache[c]={ph,idx,s:L.s,hl:L.hl,n:L.n};
}
let cur=pick(),last='',timer=0;
function style(){
  const c=/^#[0-9a-f]{6}$/i.test(S.color)?S.color:null;
  E.style.color=S.color;E.style.textShadow='0 0 .5em '+(c?c+'8c':S.color);
}
function fit(){
  if(S.size>0){E.style.fontSize=S.size+'px';return;}
  let lo=6,hi=800;
  while(hi-lo>1){const m=(lo+hi)>>1;E.style.fontSize=m+'px';
    (E.scrollWidth<=innerWidth*.92&&E.scrollHeight<=innerHeight*.88)?lo=m:hi=m;}
  E.style.fontSize=lo+'px';
}
function tick(){
  clearTimeout(timer);
  const now=new Date(),L=lang(cur),h=now.getHours(),m=now.getMinutes();
  const lines=L.ph[L.idx[(h*60+m)%L.idx.length]].slice();
  if(S.min&&m%5)lines.push(L.s[m%5-1]);
  const t=lines.join('\n');
  if(t!==last){last=t;E.replaceChildren(...lines.map(l=>{const d=document.createElement('div');d.textContent=l;return d;}));
    document.documentElement.lang=L.hl;document.title=lines.join(' ');fit();}
  timer=setTimeout(tick,60200-now.getSeconds()*1000-now.getMilliseconds());
}
// gear: visible while the mouse moves (or after a tap), the panel stays open until a click outside
let gt=0;
function showGear(){$('g').classList.add('on');clearTimeout(gt);gt=setTimeout(()=>$('g').classList.remove('on'),2500);}
addEventListener('mousemove',showGear);addEventListener('touchstart',showGear,{passive:true});
$('g').onclick=e=>{e.stopPropagation();document.body.classList.toggle('open');ui();};
$('s').onclick=e=>e.stopPropagation();
addEventListener('click',()=>document.body.classList.remove('open'));
function url(){
  const q=new URLSearchParams();
  if(!S.min)q.set('min','0');if(S.color!==DEF.color)q.set('color',S.color.replace('#',''));
  if(S.size)q.set('size',S.size);if(P.get('lang'))q.set('lang',P.get('lang'));
  const s=q.toString();return 'wordclock_desktop.html'+(s?'?'+s:'');
}
function ui(){
  $('sMin').checked=S.min;$('sCol').value=/^#[0-9a-f]{6}$/i.test(S.color)?S.color:DEF.color;$('sSize').value=S.size;
  $('sSizeV').textContent=S.size?S.size+' px':UI.auto;$('sUrl').textContent=UI.link+': '+url();
}
function set(k,v){S[k]=v;save();style();last='';tick();ui();}
$('sMin').onchange=e=>set('min',e.target.checked);
$('sCol').oninput=e=>set('color',e.target.value);
$('sRes').onclick=()=>set('color',DEF.color);
$('sSize').oninput=e=>set('size',+e.target.value);
// easter egg: arrow keys switch the language
let nt=0;
addEventListener('keydown',e=>{
  if(e.target.tagName==='INPUT')return;
  const d=e.key==='ArrowRight'?1:e.key==='ArrowLeft'?-1:0;if(!d)return;
  cur=C[(C.indexOf(cur)+d+C.length)%C.length];last='';tick();
  const n=$('n');n.textContent=lang(cur).n+' ('+cur+')';n.style.opacity=1;clearTimeout(nt);nt=setTimeout(()=>n.style.opacity=0,1500);
});
addEventListener('resize',fit);
style();tick();
</script>
</body>
</html>
'''


def main():
    cxx = shutil.which("g++") or shutil.which("clang++")
    if not cxx:
        print("no g++ found - Windows: winget install BrechtSanders.WinLibs.POSIX.UCRT"); return 1
    langs = sorted(os.path.basename(p)[8:-2] for p in glob.glob(os.path.join(SRC, "wc_lang_*.h")))
    data = {}
    with tempfile.TemporaryDirectory() as tmp:
        for lang in langs:
            meta, d = dump(cxx, tmp, lang)
            data[lang] = encode(meta, d)
    js = json.dumps(data, ensure_ascii=False, separators=(",", ":"))
    html = TEMPLATE.replace("__DATA__", js)
    old = open(OUT, encoding="utf-8").read() if os.path.isfile(OUT) else None
    if old != html:
        with open(OUT, "w", encoding="utf-8", newline="\n") as f: f.write(html)
        print("written   docs/wordclock_desktop.html (%d languages, %d KB)" % (len(data), len(html.encode()) // 1024))
    else:
        print("unchanged docs/wordclock_desktop.html")
    return 0


if __name__ == "__main__":
    sys.exit(main())
