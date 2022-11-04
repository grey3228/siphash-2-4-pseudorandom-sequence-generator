## SipHash-2-4 as pseudorandom sequence generator
Pseudorandom function SipHash-2-4 (from SipHash family of pseudorandom functions https://en.wikipedia.org/wiki/SipHash)
may be used as pseudorandom sequence generator. 

## Usage
To generate pseudorandom sequence you need to create binary:
``` shell
    gcc -c siphash.c
    gcc -c generator.c
    gcc -o gen siphash.o generator.o
```
and then launch it:
``` shell
    ./gen
```
Generated sequence will be written into `result.txt` file in same directory.
## Testing generated sequence
To test generated sequence you need to clone and install NIST Statistical Test Suite https://github.com/terrillmoore/NIST-Statistical-Test-Suite.  
  
For example, file `report.txt` contains results of testing 10^7 byte sequence, generated with key 0x0000000000000031.
Amount of bit streams = 10, length of bit stream = 10^6.