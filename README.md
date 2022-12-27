<h1 align="center">
   <b font size="15" face="arial" ><br><br>minishell</font></b></h1>
   <p align="center">
  "As beautiful as a shell" <br>
  In this case we had to understand how processes, redirections, pipes, execve and bash builtins work. We also had to learn how bash handle a command line (lexer / parser / exec).
  </a>.</br>
  <img src="https://img.shields.io/badge/c-007ACC?style=for-the-badge&logo=c&logoColor=white">
  <table  align="center">
<td>
 <b face="arial" >final mark<br><br></font></b></p>
 <img src="https://github.com/xibaochat/minishell/blob/master/minishell_mark.png">
 

</td>

<td>

| interest                     | number of team          | difficulty                      |
| ---------------------------- | ----------              | ----------                      |
|    :star::star::star:: | :cat: :cat:|  :star::star::star: :star:|

</td>
</tr>
</table>

## Subject
[minishell.pdf](https://github.com/xibaochat/minishell/blob/master/minishell.pdf)


## Usage

In the root of the repo, run:
```bash
make
```

Once the binary is created, run:
```bash
./minishell
```

Then you can use it as a basic minishell, try these commands:
```bash
./minishell
echo 'hello world'
cat Makefile
ls | grep file
cd src
echo 'hello' > myfile.txt | echo "world" >> myfile.txt | cat myfile.txt
bao
sophie 4
exit
```
![gif](https://github.com/xibaochat/minishell/blob/master/minishell.gif)
