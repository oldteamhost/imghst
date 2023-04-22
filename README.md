# imghst | ImageHost
![alt text](https://i.imgur.com/SVtWBEw.png)


**imghst** - is a utility for parsing pictures from photohosting sites.

## Info
- **Supports:** all formats.
- **Speed:** 55p hit/min
- **Program output:** File; Status; Time; Link;
- **Completely cross-platform**

## Usage
```
Imghst - is a utility for parsing pictures from photohosting sites.

usage: ./imghst [DOMAIN], [FLAGS]

arguments program:
  -h, --help            Show this help message and exit.
  -v, --version         Display version information and dependencies.
  --verbose             Display progress grab, and sys info.

arguments main:
  --db, --debug         Saving and outputting even links that are not working.
  --timeout <MS>        Set delay in ms.
  --format <.FORMAT>    Set photo format.
  --protocol <PROTOCOL> Set protocol on connect (http,https).
  --token-length <LEN>  Set the length of the generated token.

arguments user:
  --user-agent <AGENT>  Set user-agent on connect.
  --cfg-info <PATH>     Display config.
  --proxy <P:IP:PORT>   Using proxy.

arguments output:
  --count <COUNT>       Count photos.
  --path <PATH>         Set the path where the photos will be saved.
  --txt <PATH>          Save links in a text document.
  --cfg <PATH>          Use config for parsing.
```
## Default values
```
domain -          
protocol -        https://
user-agent -      "imghst by oldteam"
path -            
format -          .png
token-length -    5
count -           100
```

## Example usage config
``` C
./imghst --cfg configs/imgur.cfg
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
