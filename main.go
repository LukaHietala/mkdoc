package main

import (
	"bytes"
	"io"
	"os"

	"github.com/yuin/goldmark"
)

func main() {
	// open md file
	mdFile, err := os.Open("test.md")
	if err != nil {
		panic(err)
	}
	defer mdFile.Close()

	// read the contents
	mdContent, err := io.ReadAll(mdFile)
	if err != nil {
		panic(err)
	}

	// init goldmark
	md := goldmark.New()

	// convert to html
	var buf bytes.Buffer
	if err := md.Convert(mdContent, &buf); err != nil {
		panic(err)
	}

	// write to html
	htmlFile, err := os.Create("test.html")
	if err != nil {
		panic(err)
	}
	defer htmlFile.Close()

	_, err = htmlFile.Write(buf.Bytes())
	if err != nil {
		panic(err)
	}
}
