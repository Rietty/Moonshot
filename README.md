# Clank
## Notes on decrypting the League of Legends replay file format.

### Data Types
------
Unsigned & Little Endian
* Byte - 1 byte
* Short - 2 bytes
* Int - 4 bytes
* Long - 8 bytes

### File Header
------
#### Magic Bytes
Starts with 6 bytes with value of `52 49 4F 54 00 00` or `RIOT\0\0`. Check this to make sure it's a valid replay file.
#### File signature.
256 bytes long. Can be safely ignored(?) for the most part. Evidently not useful for decryption.
#### Offset and Length information.
26 bytes of information about the file, including length and payload/header offsets.
