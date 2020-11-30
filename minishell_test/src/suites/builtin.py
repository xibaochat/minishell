# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    builtin.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/15 18:24:43 by charles           #+#    #+#              #
#    Updated: 2020/10/29 14:16:47 by cacharle         ###   ########.fr        #
#    Updated: 2020/09/11 18:01:27 by juligonz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os

import config
import hooks
from suite import suite
from hooks import linux_discard


@suite()
def suite_echo(test):
    """ echo builtin tests """
    test("echo")
    test("echo bonjour")
    test("echo lalalala lalalalal alalalalal alalalala")
    test("echo lalalala                lalalalal      alalalalal alalalala")
    test("echo " + config.LOREM)
    test("echo -n")
    test("echo -n bonjour")
    test("echo -n lalalala lalalalal alalalalal alalalala")
    test("echo -n lalalala                lalalalal      alalalalal alalalala")
    test("echo -n " + config.LOREM)
    test("echo bonjour -n")
    test("echo -n bonjour -n")
    test("                        echo                     bonjour             je")
    test("                        echo       -n            bonjour             je")
    test("echo a '' b '' c '' d")
    test('echo a "" b "" c "" d')
    test("echo -n a '' b '' c '' d")
    test('echo -n a "" b "" c "" d')
    test("echo '' '' ''")
    test("Echo bonjour")
    test("eCho bonjour")
    test("ecHo bonjour")
    test("echO bonjour")
    test("EchO bonjour")
    test("eCHo bonjour")
    test("EcHo bonjour")
    test("eChO bonjour")
    test("Echo bonjour", exports={"PATH": "/bin:/usr/bin"})
    test("eCho bonjour", exports={"PATH": "/bin:/usr/bin"})
    test("ecHo bonjour", exports={"PATH": "/bin:/usr/bin"})
    test("echO bonjour", exports={"PATH": "/bin:/usr/bin"})
    test("EchO bonjour", exports={"PATH": "/bin:/usr/bin"})
    test("eCHo bonjour", exports={"PATH": "/bin:/usr/bin"})
    test("EcHo bonjour", exports={"PATH": "/bin:/usr/bin"})
    test("eChO bonjour", exports={"PATH": "/bin:/usr/bin"})
    test("eChO -e 'bonjo\\nur'", exports={"PATH": "/bin:/usr/bin"})
    test("echo -n -n -n -n bonjour")
    test("echo -nnnnnnnnnnnnnnnnnnnnn bonjour")
    test("echo -nnnnnnnnnnnnnnnnnnnnn -n -n -n bonjour -n -n")


@suite()
def suite_export(test):
    """ export builtin tests """
    test("export", hook=hooks.export_singleton)
    test("export", exports={"A": ""}, hook=hooks.export_singleton)
    test("export", exports={"A": "\""}, hook=hooks.export_singleton)
    test("export", exports={"A": "\t"}, hook=hooks.export_singleton)
    test("export", exports={"A": "'"}, hook=hooks.export_singleton)
    test("export", exports={"A": "a"}, hook=hooks.export_singleton)
    test("export A=a; echo $A")
    test("export A=a B=b C=c; echo $A$B$C")
    test("export A=a B=b C=c D=d E=e F=f G=g H=h I=i J=j K=k L=l"
         "M=m N=n O=o P=p Q=q R=r S=s T=t U=u V=v W=w X=x Y=y Z=z"
         "; echo $A$B$C$D$E$F$G$H$I$J$K$L$M$N$O$P$Q$R$S$T$U$V$W$X$Y$Z")
    test("export BONJOURJESUIS=a; echo $BONJOURJESUIS")
    test("export bonjourjesuis=a; echo $bonjourjesuis")
    test("export bonjour_je_suis=a; echo $bonjour_je_suis")
    test("export BONJOURJESUIS1=a; echo $BONJOURJESUIS1")
    test("export bO_nJq123o__1ju_je3234sui__a=a; echo $bO_nJq123o__1ju_je3234sui__a")
    test("export a0123456789=a; echo $a0123456789")
    test("export abcdefghijklmnopqrstuvwxyz=a; echo $abcdefghijklmnopqrstuvwxyz")
    test("export ABCDEFGHIJKLMNOPQRSTUVWXYZ=a; echo $ABCDEFGHIJKLMNOPQRSTUVWXYZ")
    test("export __________________________=a; echo $__________________________")
    test("export _bonjour_=a; echo $_bonjour_")
    test("export _=a; echo $_a")
    test("export 1=a")
    test("export BONJOURJESUIS =a")
    test("export BONJOURJESUIS= a")
    test(r"export BONJOUR\\JESUIS=a")
    test(r"export BONJOUR\'JESUIS=a")
    test(r'export BONJOUR\"JESUIS=a')
    test(r"export BONJOUR\$JESUIS=a")
    test(r"export BONJOUR\&JESUIS=a")
    test(r"export BONJOUR\|JESUIS=a")
    test(r"export BONJOUR\;JESUIS=a")
    test(r"export BONJOUR\_JESUIS=a")
    test(r"export BONJOUR\0JESUIS=a")
    test(r"export \B\O\N\ \ \ \ \ \ \ JOURJESUIS=a")
    test(r"export A=\B\O\N\ \ \ \ \ \ \ JOURJESUIS; echo $A")
    test(r"export A='bonjour je suis charles'; echo $A")
    test(r'export A="bonjour je suis charles"; echo $A')
    test(r"export A==a; echo $A")
    test(r"export A===a; echo $A")
    test(r"export A====a; echo $A")
    test(r"export A=====a; echo $A")
    test(r"export A======a; echo $A")
    test(r"export A=a=a=a=a=a; echo $A")
    test("export A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C")
    test("export 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C")
    test("export A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf '; echo $A$B$C")
    test("export A B C; echo $A$B$C")
    test("export A B C; env", hook=hooks.sort_lines)
    test("export 'AH@'=nop")
    test("export \"AH'\"=nop")
    test("export 'AH\"'=nop")
    test("export 'AH$'=nop")
    test("export 'AH!'=nop")
    test("export 'AH|'=nop")
    test("export 'AH;'=nop")
    test("export 'AH&'=nop")
    test("export 'AH\\'=nop")
    test("export $TEST", exports={"TEST": "A=a"})
    test(r"export BONJOUR\\JESUIS")
    test(r"export BONJOUR\'JESUIS")
    test(r'export BONJOUR\"JESUIS')
    test(r"export BONJOUR\$JESUIS")
    test(r"export BONJOUR\&JESUIS")
    test(r"export BONJOUR\|JESUIS")
    test(r"export BONJOUR\;JESUIS")
    test(r"export BONJOUR\_JESUIS")
    test(r"export BONJOUR\0JESUIS")


@suite()
def suite_cd(test):
    """ cd builtin tests """
    test("echo $PWD; echo $OLDPWD; cd .; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd ..; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd ../..; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd ../../..; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd ../../../..; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd ../../../../..; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd ../../../../../..; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd /; pwd; echo $PWD; echo $OLDPWD")
    # /etc is a link to /etc/private
    # hard and weird to implement with pwd
    # test("cd /etc; pwd; echo $PWD")
    test("echo $PWD; echo $OLDPWD; cd ''; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd '' ''; pwd; echo $PWD; echo $OLDPWD", hook=linux_discard)
    test("echo $PWD; echo $OLDPWD; cd '' '' ''; pwd; echo $PWD; echo $OLDPWD", hook=linux_discard)
    test("echo $PWD; echo $OLDPWD; cd ' '; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd d ''; pwd; echo $PWD; echo $OLDPWD", setup="mkdir d", hook=linux_discard)
    test("echo $PWD; echo $OLDPWD; cd d d; pwd; echo $PWD; echo $OLDPWD", setup="mkdir d", hook=linux_discard)
    test("echo $PWD; echo $OLDPWD; cd d ' '; pwd; echo $PWD; echo $OLDPWD", setup="mkdir d", hook=linux_discard)
    test("echo $PWD; echo $OLDPWD; cd $HOME; pwd; echo $PWD; echo $OLDPWD", exports={"HOME": os.getenv("HOME")})
    test("echo $PWD; echo $OLDPWD; cd /; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd /.; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd /./; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd /././././; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd //; pwd; echo $PWD; echo $OLDPWD", hook=hooks.replace_double_slash)
    test("echo $PWD; echo $OLDPWD; cd ///; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd ////; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd //////////////////////////////////////////////////////; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd; echo $PWD; echo $OLDPWD", exports={"HOME": os.getenv("HOME")})
    test("echo $PWD; echo $OLDPWD; cd ' /'; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd ' / '; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd '                  /'; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd '                  /              '; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd ' // '; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd //home; pwd; echo $PWD; echo $OLDPWD", hook=hooks.replace_double_slash)
    test("echo $PWD; echo $OLDPWD; cd ' //home'; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd '     //home    '; pwd; echo $PWD; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 000 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 001 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 002 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 003 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 004 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 005 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 006 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 007 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 010 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 020 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 030 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 040 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 050 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 060 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 070 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 100 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 200 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 300 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 400 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 500 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 600 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 700 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 755 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 644 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 311 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 111 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 222 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 333 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 0777 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 1000 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 2000 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 3000 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 4000 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 5000 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 6000 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 7000 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 1777 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 2777 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 3777 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 4777 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 5777 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 6777 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 7777 d")
    test("echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD", setup="mkdir -m 0000 d")
    test("echo $PWD; echo $OLDPWD; cd /; echo $PWD; echo $OLDPWD; unset PWD; cd /dev; echo $OLDPWD")
    test("echo $PWD; echo $OLDPWD; cd /; echo $PWD; echo $OLDPWD; export PWD=bonjour; cd /dev; echo $OLDPWD")
    # test("cd '\t'; pwd; echo $PWD");
    # test("cd '\t   \t\t\t    '; pwd; echo $PWD");
    # test("cd ~; pwd; echo $PWD"); # do we have to handle ~ ?
    # test("cd ~/..; pwd; echo $PWD");
    # test("cd ~/../..; pwd; echo $PWD");
    # test("cd $HOME; pwd; echo $PWD")


@suite()
def suite_unset(test):
    """ unset builtin tests """
    test("unset")
    test("unset A; echo $A", exports={"A": "a"})
    test("unset 'A '; echo $A", exports={"A": "a"})
    test("unset 'A='; echo $A", exports={"A": "a"})
    test("unset A B C; echo $A$B$C", exports={"A": "a", "B": "b", "C": "c"})
    test("unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C",
         exports={"A": "a", "B": "b", "C": "c"})
    test("unset 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C",
         exports={"A": "a", "B": "b", "C": "c"})
    test("unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf '; echo $A$B$C",
         exports={"A": "a", "B": "b", "C": "c"})
    test("unset A; echo $A$B$C", exports={"A": "a", "B": "b", "C": "c"})
    test("unset C; echo $A$B$C", exports={"A": "a", "B": "b", "C": "c"})
    test("unset A B C", exports={"A": "a", "B": "b", "C": "c"})
    test("unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C",
         exports={"A": "a", "B": "b", "C": "c"})
    test("unset 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C",
         exports={"A": "a", "B": "b", "C": "c"})
    test("unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf '",
         exports={"A": "a", "B": "b", "C": "c"})
    test("unset A", exports={"A": "a", "B": "b", "C": "c"})
    test("unset 'AH@'=nop")
    test("unset \"AH'\"=nop")
    test("unset 'AH\"'=nop")
    test("unset 'AH$'=nop")
    test("unset 'AH!'=nop")
    test("unset 'AH|'=nop")
    test("unset 'AH;'=nop")
    test("unset 'AH&'=nop")
    test("unset 'AH\\'=nop")


@suite()
def suite_pwd(test):
    """ pwd builtin tests """
    test("pwd")
    test("pwd", setup="cd ..")
    test("pwd", setup="cd ../..")
    test("pwd", setup="cd ../../..")
    test("pwd", setup="cd /")
    test("pwd", setup="cd $HOME")
    test("pwd | cat -e")
    test("pwd", exports={"PWD": "/etc"})
    test("unset PWD; pwd; echo $PWD")
    test("export PWD=foo; pwd; echo $PWD")
    # test("cd lnk; rmdir ../d; pwd", setup="mkdir d; ln -s d lnk")


@suite()
def suite_env(test):
    """ env builtin tests """
    test("env", hook=[hooks.sort_lines, hooks.shlvl_0_to_1])
    test("env", setup="export A=a", hook=[hooks.sort_lines, hooks.shlvl_0_to_1])
    test("env", setup="export A=a B=b C=c", hook=[hooks.sort_lines, hooks.shlvl_0_to_1])
    test("env | cat -e", setup="export A=a B=b C=c", hook=[hooks.sort_lines, hooks.shlvl_0_to_1])


@suite()
def suite_exit(test):
    """ exit builtin tests """
    test("exit")
    test("exit 1")
    test("exit 2")
    test("exit 3")
    test("exit ' 3'")
    test("exit '\t3'")
    test("exit '\t\f\r 3'")
    test("exit '3 '")
    test("exit '3\t'")
    test("exit '3\r'", hook_status=hooks.platform_status(255, 2))
    test("exit '3\t\f\r '", hook_status=hooks.platform_status(255, 2))
    test("exit '3     a'", hook_status=hooks.platform_status(255, 2))
    test("exit '3\t\t\ta'", hook_status=hooks.platform_status(255, 2))
    test("exit 0")
    test("exit -0")
    test("exit -1")
    test("exit 255")
    test("exit 256")
    test("exit 2000000")
    test("exit -2000000")
    test("exit 2147483647")
    test("exit -2147483648")
    test("exit 2147483648")
    test("exit -2147483649")
    test("exit 3147483648")
    test("exit -3147483649")
    test("exit 4294967295")
    test("exit 4294967296")
    test("exit -9223372036854775808")
    test("exit 9223372036854775807")
    test("exit -9223372036854775809", hook_status=hooks.platform_status(255, 2))
    test("exit 9223372036854775808", hook_status=hooks.platform_status(255, 2))
    test("exit 18446744073709551615", hook_status=hooks.platform_status(255, 2))
    test("exit 18446744073709551616", hook_status=hooks.platform_status(255, 2))
    test("exit +1")
    test("exit +2")
    test("exit +3")
    test("exit +0")
    test("exit +255")
    test("exit +256")
    test("exit +2000000")
    test("exit +2147483647")
    test("exit ++1", hook_status=hooks.platform_status(255, 2))
    test("exit ++2", hook_status=hooks.platform_status(255, 2))
    test("exit ++3", hook_status=hooks.platform_status(255, 2))
    test("exit ++0", hook_status=hooks.platform_status(255, 2))
    test("exit ++255", hook_status=hooks.platform_status(255, 2))
    test("exit ++256", hook_status=hooks.platform_status(255, 2))
    test("exit ++2000000", hook_status=hooks.platform_status(255, 2))
    test("exit ++2147483647", hook_status=hooks.platform_status(255, 2))
    test("exit --1", hook_status=hooks.platform_status(255, 2))
    test("exit --2", hook_status=hooks.platform_status(255, 2))
    test("exit --3", hook_status=hooks.platform_status(255, 2))
    test("exit --0", hook_status=hooks.platform_status(255, 2))
    test("exit --255", hook_status=hooks.platform_status(255, 2))
    test("exit --256", hook_status=hooks.platform_status(255, 2))
    test("exit --2000000", hook_status=hooks.platform_status(255, 2))
    test("exit --2147483647", hook_status=hooks.platform_status(255, 2))
    test("exit bonjour", hook_status=hooks.platform_status(255, 2))
    test("exit 0_", hook_status=hooks.platform_status(255, 2))
    test("exit _0", hook_status=hooks.platform_status(255, 2))
    test("exit 0123456789")
    test("exit -0123456789")
    test("exit 00000000000000000000000000000000000000000000001")
    test("exit 00000000000000000000000000000000000000000000000"
         "00000000000000000000000000000000000000000000001")
    test("exit 00000000000000000000000000000000000000000000000"
         "00000000000000000000000000000000000000000000000")
    test("exit -00000000000000000000000000000000000000000000000"
         "00000000000000000000000000000000000000000000001")
    test("exit -99999999999999999999999999999999999999999999"
         "99999999999999999999999999999999999999999999", hook_status=hooks.platform_status(255, 2))
    test("exit 99999999999999999999999999999999999999999999"
         "99999999999999999999999999999999999999999999", hook_status=hooks.platform_status(255, 2))
    test("exit 0 bonjour")
    test("exit bonjour 0", hook_status=hooks.platform_status(255, 2))
    test("exit 0 1")
    test("exit 0 1 2 3 4 5 6 7 8 9")
    test("exit " + config.LOREM, hook_status=hooks.platform_status(255, 2))