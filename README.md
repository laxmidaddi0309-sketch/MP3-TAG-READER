DESCRIPTION:
🎵MP3 Tag Reader & Editor in C
A simple command-line tool written in C to view and edit MP3 ID3v2 tags like Title, Artist, Album, Year, Genre, and Comment.

This project demonstrates:
1.File handling in C  
2.Binary file parsing  
3.Structure of ID3v2 tags  
4.Basic command-line argument parsing  

Features
View MP3 metadata:
1.Title
2.Artist
3.Album
4.Year
5.Genre
6.Comment

Edit MP3 metadata:
  1.Title (-t)
  2.Artist (-a)
  3.Album (-A)
  4.Year (-y)
  5.Genre (-m)
  6.Comment (-c)

Shows understanding of:
1.File pointers
2.Endianness handling
3.Memory allocation (malloc)
4.Linked compilation with multiple .c files

Project Structure
├── main.c        # Entry point, command-line parsing
├── view.c        # View MP3 tags
├── edit.c        # Edit MP3 tags
├── view.h        # View function prototypes
├── edit.h        # Edit function prototypes
├── types.h       # Enums and status definitions
└── README.md     # Project documentation

Compilation
Compile all source files together:

gcc main.c view.c edit.c -o mp3
Usage
🔹 View MP3 tags
./mp3 -v sample.mp3
🔹 Edit MP3 tags
./mp3 -e -t "New Song Title" sample.mp3
./mp3 -e -a "New Artist" sample.mp3
./mp3 -e -A "New Album" sample.mp3
./mp3 -e -y "2026" sample.mp3
./mp3 -e -m "Pop" sample.mp3
./mp3 -e -c "Nice song" sample.mp3

Limitations
1.Editing works only if the new tag value is not longer than the existing tag size in the MP3 file.
2.This tool performs in-place editing and does not rebuild frames.
3.Supports basic ID3v2.3 text frames only.

1.Learning Outcomes
2.Understanding MP3 ID3v2 frame structure
3.Working with binary files in C
4.Command-line argument handling
5.Modular C programming with headers and source files

Future Improvements
1.Dynamic resizing of ID3 frames
2.Backup file creation before editing
3.UTF-16 tag support
4.Better error handling
5.Windows executable support
