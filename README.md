

# ACM-Templates

:fire: This is my ACM template, which is built by xeletex. Includes number theory, graph theory, data structure, dynamic programming, string, search, simulation, greed, classical examples, etc.

Build template with `main.tex` as the core.

## How to make your template？


### 1. Installing xelatex environment

```bash
sudo apt-get install texlive-xetex
```

### 2. Create your own Tex file

```bash
mkdir your-directory && cd your-directory
touch your.tex
```

### 3. Edit your.tex

+ Example

```tex
\documentclass[../main.tex]{subfiles}  # your.tex as a subfile, pointing to main.tex

\begin{document}

your content...

\end{document}
```

### 4. Add your section in contents 


```bash
cd .. 
vim main.tex
```

+ Example

```tex
\documentclass[]{article}

...

\begin{document}

...
\section{your section name}
\subfile{your-directory/your.tex}
...

\end{document}
```



### 5. Rebuild

```bash
xelatex main.tex
```



The generated `main.pdf` will be your template.



## Thanks

+ I'd appreciate a star if you find this helpful.
+ Special thanks to [SmartvV](https://codeforces.com/profile/SmartvV),[Carered](https://codeforces.com/profile/Carered), [Luxaky](https://codeforces.com/profile/Luxaky),accompany me through ACM.



## License

[MIT](http://opensource.org/licenses/MIT)



