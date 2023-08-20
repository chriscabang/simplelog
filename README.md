# Simple Log

[![Licence](https://img.shields.io/github/license/Ileriayo/markdown-badges?style=for-the-badge)](./LICENSE)

Simple logging mechanism for C projects. 

## Compile

Compile your C project with `libsimplelog.a` library.

```
$> gcc libsimplelog.a -o test
```

And that's it!

## Usage

Drop the header file in your C project and include it in your source to log.

```c
#include <stdio.h>

#include <simplelog.h>

int main() {
  printf("Hello World\n");

  log_info("this is info\n");
  log_debug("and this prints debug\n");
  log_error("while this logs error\n");
  log_warn("and this a warning\n");

  return 0;
}
```

```console
%> ./bin/test
Hello World
[    12:12:42.753] LOG_INFO   main.c:main():8      : this is info
[    12:12:42.753] LOG_DEBUG  main.c:main():9      : and this prints debug
[    12:12:42.753] LOG_ERROR  main.c:main():10     : while this logs error
[    12:12:42.753] LOG_WARN   main.c:main():11     : and this a warning
```


## License

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

[MIT](LICENSE) © Chris Cabang