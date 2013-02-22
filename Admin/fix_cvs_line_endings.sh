for i in `find . -name "*.[ch]"`; do perl -i -ne 's/\r/\n/g && print' \"$i\"; done
