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

## 安装`zsh`和`oh-my-zsh`
1. 安装`zsh`
```shell
# 下载源码
wget https://sourceforge.net/projects/zsh/files/zsh/5.8/zsh-5.8.tar.xz
# 解压
tar xvf zsh-5.8.tar.xz
# 编译
cd zsh-5.8
./configure --prefix=$HOME/software/zsh-5.8
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
# 下载脚本
wget https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh
# 修改脚本，删除以下内容
CHECK_ZSH_INSTALLED=$(grep /zsh$ /etc/shells | wc -l)
if [ ! $CHECK_ZSH_INSTALLED -ge 1 ]; then
    printf "${YELLOW}Zsh is not installed!${NORMAL} Please install zsh first!\n"
    exit
fi
unset CHECK_ZSH_INSTALLED
# 运行安装
./install.sh
```