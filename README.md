<p align="center">
	<img alt="scilog" src="https://github.com/Iarfen/scilog/blob/master/docs/logo-scilog.svg?sanitize=true" width="550">
</p>
scilog is under development, it can't be installed yet, so don't try it :D

**scilog** is an small utility to track research activity, divided between learn and project activities, it allows to don't lose time remembering the work done during the week or month, cause it tracks everything you add.
scilog works with .xml files as the following, which are edited using any xml editor (or the notepad):

```xml
<?xml version="1.0" encoding="UTF-8"?>
<scilog>
	<entry type="learn" subtype="documentation" topic="rapidxml" date="07/12/2017">I've readed about XML parsers, and I've finally decided to learn rapidxml to use for my C++ projects.</entry>
	<entry type="project" subtype="programming" topic="mind-fiction" date="07/12/2017">I've programmed the list and summary commands of scilog CLI.</entry>
</scilog>
```

A scilog file is very simple. ```<scilog>``` is the general tag to use for <scilog> files. ```<entry>``` represents any log entry to register. Each entry can be of type learn or of type project. For learn entries, they can be of subtype documentation, book, planification or use. For project entries, they can be of subtype programming, planification, design, theory. Also, every entry contains the information of the topic of work (written using hyphens and in small case) and the date of work. The contents of each entry describes what has been done.

You can write scilog files with any xml editor you like, or with any notepad. There's no problem with what you choose to use: everything is useful to edit the scilog file and add new entries.

# Install
### Linux
```
apt-get install scilog
```
### Windows
```
cmake -G "MSYS Makefiles" (or "MinGW Makefiles" if you use MinGW)
make
make install
```

# Suggestions
If you've any **suggestions** related to scilog, feel free to send them to **ismael.correa.castro@gmail.com**

# Author
scilog has been created by **Ismael Correa C.** You can email me at **ismael.correa.castro@gmail.com** if you have any question related to scilog.
