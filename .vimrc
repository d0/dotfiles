set incsearch
set ignorecase
set smartcase
set showmatch
set gdefault

set smartindent
set tabstop=4
set shiftwidth=4
set softtabstop=4
set expandtab

set backspace=indent,eol,start
set ttyfast
set cursorline
set hlsearch
set wildmenu
set wildmode=list:longest
set laststatus=2
set scrolloff=3
set number
set ruler
set showcmd
set showmode
set autoindent
set cindent

set wrap
set textwidth=79
set colorcolumn=85

set nocompatible

filetype off
call pathogen#infect()

syntax enable
set ofu=syntaxcomplete#Complete
if v:version >= 600
    filetype plugin on
    filetype indent on
else
    filetype on
endif

if v:version >= 700
    set omnifunc=syntaxcomplete#Complete " override built-in C omnicomplete with C++ OmniCppComplete plugin
    let OmniCpp_GlobalScopeSearch   = 1
    let OmniCpp_DisplayMode         = 1
    let OmniCpp_ShowScopeInAbbr     = 0 "do not show namespace in pop-up
    let OmniCpp_ShowPrototypeInAbbr = 1 "show prototype in pop-up
    let OmniCpp_ShowAccess          = 1 "show access in pop-up
    let OmniCpp_SelectFirstItem     = 1 "select first item in pop-up
    let OmniCpp_MayCompleteDot      = 1 "complete after '.'
    let OmniCpp_MayCompleteArrow    = 1 "complete after '->'
    let OmniCpp_MayCompleteScope    = 1 "complete after '->'
    set completeopt=menuone,menu,longest
endif

set background=dark
let g:solarized_termtrans=1
colorscheme solarized

highlight ExtraWhitespaces ctermbg=darkgreen guibg=lightgreen
match ExtraWhitespaces /\s\+$/

set tags=./tags;$HOME "Recursively search for the tags file up til $HOME
" build tags of your own project with Ctrl-F12
map <C-F12> :!ctags -R --sort=yes --c++-kinds=+p --fields=+iaS --extra=+q .<CR>
"
"Disable arrow keys
noremap <up> <nop>
noremap <down> <nop>
noremap <left> <nop>
noremap <right> <nop>
inoremap <up> <nop>
inoremap <down> <nop>
inoremap <left> <nop>
inoremap <right> <nop>

"Use "," as leader key
let mapleader = ","

"Use <leader><space> to clean search highlighting
nnoremap <leader><space> :noh<cr>

"Use <tab> instead of % to match brackets
nnoremap <tab> %
vnoremap <tab> %

nnoremap <f2> :NERDTreeToggle<cr>

"Improve up/down navigation for wrapped lines
nnoremap j gj
nnoremap k gk

"Turn off expandtab for Makefiles
autocmd FileType make setlocal noexpandtab
