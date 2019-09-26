# OrgModeParser, a parser for Emacs Org Mode files, written in C++

OrgModeParser parses Emacs OrgMode files and builds a C++ object tree
that represents the Org files structure. This functionality is made
available in a library that can be integrated into other
applications. The motivation behind it was to be able to integrate
existing applications written in C++ with OrgMode. For example, a
calendar application could write an OrgMode file to make TODO items
available in the OrgMode agenda. An email program could offer
functionality to add TODO items from the user's inbox. Et cetera. The
possibilities are endless.

## Quick Start

### Installation

OrgModeParser requires Qt 5.3 and CMake 3.2. Newer versions should
work as well. On most Linux distributions, shipped packages should be
fine. Installation is straight-forward:

    > git clone https://github.com/mirkoboehm/OrgModeParser.git
    > mkdir OrgModeParser/build
    > cd OrgModeParser/build
    > cmake ../
    > make
    > make install

This install the OrgModeParser dynamic library, as well as the tools
it provides. The default installation prefix is /usr/local.

### Usage

An OrgMode file is parsed by passing an open text stream to the parse method:

    > OrgElement::Pointer orgfile = parser.parse(&stream, inputFile);

_orgfile_ now holds a hierarchical data structure of the content of
the file.  The concept is similar to DOM processing of HTML
files. OrgMode file sections are called headlines and start with an
asterisk. Filtering can be used to create flat lists of headlines that
match certain criteria. All headlines can be collected using the
element type _Headline_ like this:

    > auto const headlines = findElements<Headline>(orgfile);

Headline is a subclass of OrgElement. Other element types are for
example clock lines or drawers. By adding a predicate, additional
criteria can be implemented:

    > auto const todos = findElements<Headline>(orgfile, isTODO);

See the _TODOCounter_ demo for more a compilable version of these
examples.  The Writer class can be used to write out OrgMode files.

### Tools

As of now, OrgModeParser installs OrgModeParser_ClockTimeSummary, a
tool that create a one-line summary of the OrgMode clock time entries
created this week. Its output looks something like this:

    02:10: TODO Write README for OrgModeParser   00:00/26:59

The left duration shows the time spend on the currently active task,
followed by the item headline. On the right, it displays the totals of
the time clocked today, and this week.

### Library

All functionality of the parser is contained in the OrgModeParser
library. The content of an OrgMode file is represented as a tree of
objects that represent the various elements of the file, like
headlines, drawers, properties, tags and clocklines. Other classes
like Clock or Property provide access to the values of the tree
elements. A simple demo that counts the number of TODO items in an
OrgMode file can be found in Demos/TODOCounter:

```c++
    OrgElement::Pointer orgfile = parser.parse(&stream, inputFile);
    auto const headlines = findElements<Headline>(orgfile);
    wcout << "Number of headlines: " << headlines.count() << endl;
    auto isTODO = [](const Headline::Pointer& element) {
        return element->caption().startsWith(QStringLiteral("TODO"));
    };
    auto const todos = findElements<Headline>(orgfile, isTODO);
    wcout << "Number of TODOs: " << todos.count() << endl;
```

### Tests

OrgModeParser is developed in a test-driven development model. To run
the tests, go to the build directory and run `make test`.

## Contributing

To fix or extend the functionality of OrgModeParser, provide examples
of Org files and specify where OrgModeParser parses it wrong or does
not implement features. When submitting pull requests on
Github. remember every new piece of code needs to be auto-tested.
