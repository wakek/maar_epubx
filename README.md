# ebook_toolkit

This project provides tools to parse, read, render, or write multiple ebook file types in flutter/dart.

Below are a list of attributions to the projects that are part of the foundation of ebook_toolkit:
- EPUB: Ebook_toolkit started as a fork of [ebook_toolkit](https://github.com/orthros/dart-epub) which is itself a fork of [dart-epub](https://github.com/ScerIO/ebook_toolkit.dart). The [dart-epub] project is "an Epub Reader and Writer for Dart inspired by [this fantastic C# Epub Reader](https://github.com/versfx/EpubReader)"
- PDF: The PDF reader implementation in this plugin is heavily inspired by [flutter_pdf_render](https://github.dev/espresso3389/flutter_pdf_render).

## EPUB Example
```dart

//Get the epub into memory somehow
String fileName = 'sample.epub';
String fullPath = path.join(io.Directory.current.path, fileName);
var targetFile = new io.File(fullPath);
List<int> bytes = await targetFile.readAsBytes();


// Opens a book and reads all of its content into memory
EpubBook epubBook = await EpubReader.readBook(bytes);

// COMMON PROPERTIES

// Book's title
String title = epubBook.Title;

// Book's authors (comma separated list)
String author = epubBook.Author;

// Book's authors (list of authors names)
List<String> authors = epubBook.AuthorList;

// Book's cover image (null if there is no cover)
Image coverImage = epubBook.CoverImage;


// CHAPTERS

// Enumerating chapters
epubBook.Chapters.forEach((EpubChapter chapter) {
// Title of chapter
String chapterTitle = chapter.Title;

// HTML content of current chapter
String chapterHtmlContent = chapter.HtmlContent;

// Nested chapters
List<EpubChapter> subChapters = chapter.SubChapters;
});


// CONTENT

// Book's content (HTML files, stylesheets, images, fonts, etc.)
EpubContent bookContent = epubBook.Content;


// IMAGES

// All images in the book (file name is the key)
Map<String, EpubByteContentFile> images = bookContent.Images;

EpubByteContentFile firstImage = images.values.first;

// Content type (e.g. EpubContentType.IMAGE_JPEG, EpubContentType.IMAGE_PNG)
EpubContentType contentType = firstImage.ContentType;

// MIME type (e.g. "image/jpeg", "image/png")
String mimeContentType = firstImage.ContentMimeType;

// HTML & CSS

// All XHTML files in the book (file name is the key)
Map<String, EpubTextContentFile> htmlFiles = bookContent.Html;

// All CSS files in the book (file name is the key)
Map<String, EpubTextContentFile> cssFiles = bookContent.Css;

// Entire HTML content of the book
htmlFiles.values.forEach((EpubTextContentFile htmlFile) {
String htmlContent = htmlFile.Content;
});

// All CSS content in the book
cssFiles.values.forEach((EpubTextContentFile cssFile){
String cssContent = cssFile.Content;
});


// OTHER CONTENT

// All fonts in the book (file name is the key)
Map<String, EpubByteContentFile> fonts = bookContent.Fonts;

// All files in the book (including HTML, CSS, images, fonts, and other types of files)
Map<String, EpubContentFile> allFiles = bookContent.AllFiles;


// ACCESSING RAW SCHEMA INFORMATION

// EPUB OPF data
EpubPackage package = epubBook.Schema.Package;

// Enumerating book's contributors
package.Metadata.Contributors.forEach((EpubMetadataContributor contributor){
String contributorName = contributor.Contributor;
String contributorRole = contributor.Role;
});

// EPUB NCX data
EpubNavigation navigation = epubBook.Schema.Navigation;

// Enumerating NCX metadata
navigation.Head.Metadata.forEach((EpubNavigationHeadMeta meta){
String metadataItemName = meta.Name;
String metadataItemContent = meta.Content;
});

// Writing Data
var written = await EpubWriter.writeBook(epubBook);

// You can even re-read the book into a new object! 
var bookRoundTrip = await EpubReader.readBook(written);
```