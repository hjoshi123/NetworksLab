set ns [new Simulator]

set traceFile [open 5.tr w]
$ns trace-all $traceFile
set namFile [open 5.nam w]
$ns namtrace-all $namFile

proc finish {} {
    global ns namFile traceFile
    $ns flush-trace
    close $traceFile
    close $namFile

    exec awk -f stats.awk 3.tr &
    exit 0
}

for {set i 0} {$i < 6} {incr i} {
    set n($i) [$ns node]
}

$ns duplex-link $n(0) $n(2) 2Mb 10ms DropTail
$ns duplex-link $n(1) $n(2) 2Mb 10ms DropTail
$ns simplex-link $n(2) $n(3) 0.3Mb 100ms DropTail
$ns simplex-link $n(3) $n(2) 0.3Mb 100ms DropTail

set lan [$ns newLan "$n(3) $n(4) $n(5)" 0.5Mb 40ms LL Queue/DropTail MAC/Csma/Cd Channel]

$ns duplex-link-op $n(0) $n(2) orient right-down
$ns duplex-link-op $n(1) $n(2) orient right-up
$ns simplex-link-op $n(2) $n(3) orient right
$ns simplex-link-op $n(3) $n(2) orient left

$ns queue-limit $n(2) $n(3) 20
$ns simplex-link-op $n(2) $n(3) queuePos 0.5

set tcp [new Agent/TCP]
$ns attach-agent $n(0) $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n(4) $sink

set ftp [new Application/FTP]
$ftp set type_ FTP
$ftp attach-agent $tcp

set upd0 [new Agent/UDP]
$ns attach-agent $n(1) $upd0
set null0 [new Agent/Null]
$ns attach-agent $n(5) $null0
$ns connect $upd0 $null0

set cbr [new Application/Traffic/CBR]
$cbr set type_ CBR
$cbr set packetSize_ 1000
$cbr set rate_ 0.2Mb
$cbr set random_ false
$cbr attach-agent $upd0

$ns at 0.1 "$cbr start"
$ns at 1.0 "$ftp start"
$ns at 124.0 "$ftp stop"
$ns at 124.5 "$cbr stop"
$ns at 125.0 "finish"

$ns run



