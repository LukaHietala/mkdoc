Simple and fast app for generating docs. Built C and md4c. Supports CommonMark 0.31.2. Made for my personal use/projects. 


## Requirements

- C compiler (GCC)
- make
- git
- md4c library (libmd4c-dev on Debian)

Follows: https://www.kernel.org/doc/html/v6.17/process/coding-style.html

## Building

```bash
make
```

## Usage

```bash
./mkdoc <input.md> <output.html>
```
Input is unsanitized, so make sure that markdown is trusted. 

Since the input is unsanitized, you can directly add custom HTML and JS to the markdown files. (totally worth it)

```html
# Kisumirri

Picture of a cat:

<script>
    fetch('https://cataas.com/cat?json=true')
        .then(response => response.json())
        .then(data => {
            const img = document.createElement('img');
            img.src = data.url;
            document.body.appendChild(img);
        })
        .catch(error => console.error('error:', error));
</script>
```