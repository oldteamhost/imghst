# imghst | ImageHost
![alt text](https://i.imgur.com/7SlZJb1.png)


**imghst** - is a utility for parsing pictures from photohosting sites.

## Info
- **Supports:** all formats.
- **Speed:** 55p hit/min
- **Program output:** File; Status; Time; Link;
- **Completely cross-platform**

## Usage
```
Imghst - is a utility for parsing pictures from photohosting sites.

usage: ./imghst [DOMAIN] [FLAGS]

arguments program:
  -h, --help            Show this help message and exit.
  -v, --version         Display version information and dependencies.

arguments main:
  --db, --debug         Saving and outputting even links that are not working.
  --timeout <MS>        Set delay in ms.
  --user-agent <AGENT>  Set user-agent on connect.
  --format <.FORMAT>    Set photo format.
  --protocol <PROTOCOL> Set protocol on connect (http,https).
  --token-length <LEN>  Set the length of the generated token.

arguments output:
  --count <COUNT>       Count photos.
  --path <PATH>         Set the path where the photos will be saved.
  --txt <PATH>          Save links in a text document.
  --cfg <PATH>          Use config for parsing.
```
# Default values
```

```
## Example usage config
``` C
./imghst --cfg configs/imgur.cfg
```
```
domain=i.imgur.com
protocol=https
user-agent=oldteam
txt_path=false
path=default
format=.png
token_length=5
count=100
timeout=false
debug=false
```


## Compile linux
ARCH  
- sudo pacman -S curl

DEBIAN  
- sudo apt-get install libcurl4-openssl-dev
- -----------
- git clone https://github.com/oldteamhost/imghst.git
- cd imghst
- make
