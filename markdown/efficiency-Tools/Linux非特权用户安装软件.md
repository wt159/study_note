[toc]

# Linux下非特权用户安装软件
1. 下载源码
2. 编译可执行程序
3. 设置用户环境变量

## 安装`tree`

```shell
# 下载源码
wget http://mama.indstate.edu/users/ice/tree/src/tree-1.7.0.tgz
# 解压
tar zxvf tree-1.7.0.tgz
# 编译
cd tree-1.7.0
make
# 设置环境变量
vi ~/.bashrc
# 添加内容
export PATH=/home/user/tree-1.7.0:$PATH
# 生效
source ~/.bashrc
```
## 安装 `ncurses-devel`
```shell
# 下载
wget http://ftp.gnu.org/gnu/ncurses/ncurses-6.0.tar.gz
# 解压
tar zxvf ncurses-6.0.tar.gz
# 
cd ncurses-6.0
# 配置
./configure --with-shared --without-debug --without-ada --enable-overwrite --prefix=$HOME/usr/ncurses-6.0
# 编译
make
make install
```
## 安装`zsh`和`oh-my-zsh`
1. 安装`zsh`
```shell
# 下载源码
wget https://sourceforge.net/projects/zsh/files/zsh/5.8/zsh-5.8.tar.xz
# 解压
tar xvf zsh-5.8.tar.xz
# 编译
cd zsh-5.8
./configure --prefix=$HOME/usr/zsh-5.8
make && make install
# 设置环境变量
vi ~/.bashrc
# 添加内容
123 export PATH=$PATH:/home/user/software/zsh-5.8/bin
124 export SHELL=`which zsh`
125 exec `which zsh` -l
# 生效
source ~/.bashrc
```
2. 安装 `oh-my-zsh`
```shell
# 自动安装：
$ wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | sh
# 手动安装
$ git clone git://github.com/robbyrussell/oh-my-zsh.git ~/.oh-my-zsh
$ cp ~/.oh-my-zsh/templates/zshrc.zsh-template ~/.zshrc

```

## Q&A
### 编译`zsh`出错

错误：
```
configure: error: "No terminal handling library was found on your system. This is probably a library called curses or ncurses. You may need to install a package called 'curses-devel' or 'ncurses-devel' on your system"
```
解决方法：
安装`curses-devel`或`ncurses-devel`

### 编译`ncurses-devel`出错

错误：
```

```
解决方法：
修改`ncurses/base/MKlib_gen.sh`文件
```patch
--- a/ncurses/base/MKlib_gen.sh
+++ b/ncurses/base/MKlib_gen.sh
@@ -474,11 +474,22 @@ sed -n -f $ED1 \
    -e 's/gen_$//' \
    -e 's/  / /g' >>$TMP

+cat >$ED1 <<EOF
+s/  / /g
+s/^ //
+s/ $//
+s/P_NCURSES_BOOL/NCURSES_BOOL/g
+EOF
+
+# A patch discussed here:
+#  https://gcc.gnu.org/ml/gcc-patches/2014-06/msg02185.html
+# introduces spurious #line markers.  Work around that by ignoring the system's
+# attempt to define "bool" and using our own symbol here.
+sed -e 's/bool/P_NCURSES_BOOL/g' $TMP > $ED2
+cat $ED2 >$TMP
+
 $preprocessor $TMP 2>/dev/null \
-| sed \
-   -e 's/  / /g' \
-   -e 's/^ //' \
-   -e 's/_Bool/NCURSES_BOOL/g' \
+| sed -f $ED1 \
 | $AWK -f $AW2 \
 | sed -f $ED3 \
 | sed \
```