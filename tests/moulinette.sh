../recalage ~/exemple/ex1/status.pgm ~/exemple/ex1/nuage.txt > /tmp/ex1.out
if [ -r "/tmp/1.ref" ]; then
else
    ~yaka/pub/bin/recalage ~/exemple/ex1/status.pgm ~/exemple/ex1/nuage.txt > /tmp/ex1.ref 2> /dev/null
fi

./moulinette /tmp/ex1.out /tmp/ex1.ref
