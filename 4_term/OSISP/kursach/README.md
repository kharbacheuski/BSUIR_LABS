# Linux DD comand clone



## Using

### ./dd https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js textCopy.js
### ./dd ./data/text.txt textCopy.txt -b 8 -s 0 -sk 0 -p -u

## Flags:

- -b - buff size
- -s - seek size (buf)
- -sk - skip size (buf)
- -u - text to uppercase
- -l - text to lowercase
- -p - show progress bar
