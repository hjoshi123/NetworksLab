BEGIN {
    count = 0;
}
{
    event = $1;

    if (event == "d") {
        count++;
    }
}
END {
    printf ("Total number of packets dropped %d\n", count);
}