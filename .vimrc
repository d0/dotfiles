set incsearch
set ignorecase
set smartcase

set smartindent
set tabstop=4
set shiftwidth=4
set expandtab

set backspace=2
set hlsearch

set wrap
set number
set ruler

call pathogen#infect()
filetype plugin indent on
syntax enable
set background=dark
let g:solarized_termtrans=1
let g:solarized_termcolors=16
colorscheme solarized

highlight ExtraWhitespaces ctermbg=darkgreen guibg=lightgreen
match ExtraWhitespaces /\s\+$/

"Disable arrow keys
noremap <up> <nop>
noremap <down> <nop>
noremap <left> <nop>
noremap <right> <nop>
inoremap <up> <nop>
inoremap <down> <nop>
inoremap <left> <nop>
inoremap <right> <nop>

"Improve up/down navigation for wrapped lines
nnoremap j gj
nnoremap k gk

"Turn off expandtab for Makefiles
autocmd FileType make setlocal noexpandtab
