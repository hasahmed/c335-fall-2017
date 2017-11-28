let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/classes/C335-Fall2017/final
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1 helpers.h
badd +10 lcdutil.h
badd +1 play_audio.h
badd +1 helpers.c
badd +37 lcdutil.c
badd +57 main.c
badd +1 play_audio.c
badd +14 player.h
badd +41 Makefile
badd +5 player.c
badd +7 general_util.h
badd +1 general_util.c
badd +1 game_utils.h
badd +1 game_utils.c
badd +7 game_util.c
badd +5 game_util.h
badd +5 ../driver/src/f3d_systick.c
badd +359 ../driver/src/f3d_lcd_sd.c
badd +75 ../driver/inc/f3d_lcd_sd.h
badd +3 nunchuk_util.c
badd +16 nunchuk_util.h
badd +4 ../driver/inc/f3d_systick.h
badd +3 main.h
badd +1 ../driver/src/f3d_accel.c:w
badd +0 game_objs.h
args helpers.c lcdutil.c main.c play_audio.c helpers.h lcdutil.h play_audio.h
edit main.c
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
6argu
edit main.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 48 - ((28 * winheight(0) + 27) / 55)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
48
normal! 017|
tabedit lcdutil.c
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
edit lcdutil.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 31 - ((30 * winheight(0) + 27) / 55)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
31
normal! 05|
tabedit player.c
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
edit player.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 5 - ((4 * winheight(0) + 27) / 55)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
5
normal! 0
tabedit player.h
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
edit player.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 13 - ((12 * winheight(0) + 27) / 55)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
13
normal! 0
tabedit nunchuk_util.h
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
edit nunchuk_util.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 8 - ((7 * winheight(0) + 27) / 55)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
8
normal! 0
tabedit game_util.h
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
edit game_util.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 29 - ((28 * winheight(0) + 27) / 55)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
29
normal! 02|
tabedit nunchuk_util.c
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
edit nunchuk_util.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 4 - ((3 * winheight(0) + 27) / 55)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
4
normal! 04|
tabnext 4
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
