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
let g:solarized_termcolors=16
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

"Improve up/down navigation for wrapped lines
nnoremap j gj
nnoremap k gk

"Turn off expandtab for Makefiles
autocmd FileType make setlocal noexpandtab
