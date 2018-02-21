#!/usr/bin/awk -f

# cat test.lst | grep '^ \?[0-9a-f]\+:'

/^ ?[0-9a-f].+:/ {
    print "                                                     " $0
    last_line = "assembly"
}

!/^ ?[0-9a-f].+:/ {
    if ("assembly" == last_line) {
        print ""
        print ""
    }

    print $0
    last_line = "source"
}
