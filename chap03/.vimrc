set number
syntax on
set autoindent
set cindent
set smartindent
set tabstop=4
set shiftwidth=4
set softtabstop=4
set hlsearch
set expandtab
autocmd FileType make setlocal noexpandtab

"colorscheme 적용
"set background=dark    " Light theme is used by default
"set t_Co=256
"colorscheme PaperColor

func! Man()
	let sm = expand("<cword>")
	exe "!man -S 2:3:4:5:6:7:8:9:tcl:n:l:p:o ".sm
endfunc
nmap ,ma :call Man()<CR><CR>

nnoremap <F2> :set invpaste paste?<CR>
set pastetoggle=<F2>
