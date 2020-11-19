# gpioreg
<br>
Build with:<br>
<br>
`$ gcc -o gpioreg -lbcm_host gpioreg.c`<br>
<br>
Usage:<br>
<br>
`$ gpioreg` lists all registers<br>
`$ gpioreg n` where n=0 to 60 lists detailed information on that register<br>
`$ gpioreg 0xnn` is an alternate where n=00 to f0 <br>
