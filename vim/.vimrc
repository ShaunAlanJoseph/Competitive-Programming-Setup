set nocompatible autoread
syntax on

set number relativenumber showcmd cursorline " Visual

" Constants
let mapleader = " "
" use shellescape() // fnameescape() if req to escape special chars

" Maps
imap kj <Esc>

" Indents
set tabstop=4
set shiftwidth=4
set softtabstop=4
set autoindent smartindent nowrap

" Splits && Tabs
set splitbelow splitright
nnoremap <C-h> <C-w>h
nnoremap <C-l> <C-w>l
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <leader>h :bprev<CR>
nnoremap <leader>l :bnext<CR>

" Input / Output
let input_file = expand("%:p:h") . "/.input"
let output_file = expand("%:p:h") . "/.output"

function! OpenIOFiles()
	let input_exists = bufwinnr(g:input_file) > 0
	let output_exists = bufwinnr(g:output_file) > 0
	if !input_exists && !output_exists
		silent execute "vsplit " . g:input_file
		vertical resize 60
		silent execute "split " . g:output_file
		wincmd h
	endif
endfunction

function! ClearInput()
	call OpenIOFiles()
	wincmd l
	wincmd k
	%delete
endfunction

command! IO call OpenIOFiles()

noremap <A-1> <Esc>:call ClearInput()<CR>
inoremap <A-1> <Esc>:call ClearInput()<CR>

" Competitive Programming Setup
function! CPSetup()
	%delete
	execute "0read " . g:snip_path . "cp.cpp"
	call feedkeys("15ji\t")
endfunction

nnoremap cp<Tab> :call CPSetup()<CR>
nnoremap cpio<Tab> :IO<CR>:call CPSetup()<CR>

" Snippets
let snip_path = expand("~/cp/snippets/")

inoremap {<CR> {<CR>}<Esc>O
nnoremap +<Tab> :r <C-R>=snip_path<CR>

" Build
let compiled_file = expand("%:p:h") . "/a.out"
let time_limit = 3 " (float) seconds

function! BuildFile()
	silent write

	let src = expand("%:p")
	let build_command = "g++ -O2 -Wall -std=c++17 " . src . " -o " . g:compiled_file " with optimization
	" let build_command = "g++ -std=c++17 " . src . " -o " . g:compiled_file " no optimization
	let result = system(build_command)

	if v:shell_error
		echohl WarningMsg | echo "Build Failed!" | echohl None
		echo result
		return 0
	else
		echohl WildMenu | echo "Build Succeeded!" | echohl None
	endif
	return 1
endfunction

function! BuildAndRunWithFileIO()
	call OpenIOFiles()
	silent wall
	wincmd h

	if !BuildFile()
		return
	endif

	let run_command = "timeout " . g:time_limit . "s time -f \"%e\" " . g:compiled_file . " < " . g:input_file . " > " . g:output_file
	echo run_command
	let result = trim(system(run_command))
	if v:shell_error
		if v:shell_error == 124
			echohl WarningMsg | echo "Run Timed Out!" | echohl None
		else
			echohl WarningMsg | echo "Run Failed!" | echohl None
		echo result
		endif
		return
	else
		redraw
		echohl WildMenu | echo "Run Succeeded!" | echohl None | echon " ~ " . result . "s"
	endif

	silent checktime
endfunction$

function! BuildAndRunWithTermIO()
	if !BuildFile()
		return
	endif

	execute "terminal " . g:compiled_file
endfunction

noremap <A-r> <Esc>:call BuildAndRunWithFileIO()<CR>
inoremap <A-r> <Esc>:call BuildAndRunWithFileIO()<CR>

noremap <A-t> <Esc>:call BuildAndRunWithTermIO()<CR>
inoremap <A-t> <Esc>:call BuildAndRunWithTermIO()<CR>

" Clipboard
function! GetBufData()
	return join(getline(1, '$'), "\n")
endfunction

function! GetFilePath()
	return expand("%:p")
endfunction

function! CopyToClipboard(data)
	call system("wl-copy", a:data)
	echohl WildMenu | echo "Copied to Clipboard!" | echohl None
endfunction

function! PasteToInput()
	call OpenIOFiles()
	call system("wl-paste > " . g:input_file)
	echohl WildMenu | echo "Pasted from Clipboard!" | echohl None
	silent checktime
endfunction

nnoremap <A-y> :call CopyToClipboard(GetBufData())<CR><CR>
inoremap <A-y> <Esc>:call CopyToClipboard(GetBufData())<CR><CR>
vnoremap <A-y> "yy:call CopyToClipboard(getreg('"'))<CR><CR>

nnoremap <A-f> :call CopyToClipboard(GetFilePath())<CR><CR>
inoremap <A-f> <Esc>:call CopyToClipboard(GetFilePath())<CR><CR>

nnoremap <A-v> :call PasteToInput()<CR>
inoremap <A-v> <Esc>:call PasteToInput()<CR>

" Gnome Terminal Compatibility
"" Alt + AlphaNum 
let c = '0'
while c <= 'z'
	exec "set <A-" . c . ">=\e" . c
	exec "imap \e" . c . " <A-" . c . ">"
	if c == '9'
		let c = 'a'
	else
		let c = nr2char(char2nr(c) + 1)
	endif
endw
