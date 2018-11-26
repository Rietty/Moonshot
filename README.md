# Clank
## Notes on decrypting the League of Legends replay file format.

### Data Types
Unsigned & Little Endian
* Byte - 1 byte
* Short - 2 bytes
* Int - 4 bytes
* Long - 8 bytes

### File Header
#### Magic Bytes
Starts with 6 bytes with value of `52 49 4F 54 00 00` or `RIOT\0\0`. Check this to make sure it's a valid replay file.
#### File signature.
256 bytes long. Can be safely ignored for the most part. Evidently not useful for decryption.
#### Offset and Length information.
26 bytes of information about the file, including length and offsets.
* Header length (2 bytes)
* File length (4 bytes)
* Metadata offset (4 bytes)
* Metadata length (4 bytes)
* Data header offset (4 bytes)
* Data header length (4 bytes)
* Data offset (4 bytes)

### JSON Metadata
Is located at the metadata offset indicated in the file header and is the indicated number of bytes long. Is formated in JSON and can simply be read as is. Contains information about stats, keyframes, chunks, game length and game verison.

### Data header
Is located at offset indicated by the file header. (Basically right after JSON metadata) has a fixed length and a variable length. Fixed length of 34 bytes + extra bytes based on the indicated key.
* Game ID (8 bytes)
* Game length (4 bytes) - Milliseconds
* Keyframe count (4 bytes)
* Total chunk count (4 bytes)
* Specific chunk ID (4 bytes)
* Another chunk ID (4 bytes)
* Keyframe length/interval (4 bytes) - Milliseconds
* Variable byte length (2 bytes) - Probably encryption key information.
* Encryption key (Indicated length, string, encoded in some manner) - Required to decrypt chunk + keyframe data.
