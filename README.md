# Moonshot
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
* Header length (Short)
* File length (Int)
* Metadata offset (Int)
* Metadata length (Int)
* Data header offset (Int)
* Data header length (Int)
* Data offset (Int)

### JSON Metadata
Is located at the metadata offset indicated in the file header and is the indicated number of bytes long. Is formated in JSON and can simply be read as is. Contains information about stats, keyframes, chunks, game length and game verison.

### Data header
Is located at offset indicated by the file header. (Basically right after JSON metadata) has a fixed length and a variable length. Fixed length of 34 bytes + extra bytes based on the indicated key.
* Game ID (Long)
* Game length (Int) - Milliseconds
* Keyframe count (Int)
* Total chunk count (Int)
* Specific chunk ID (Int)
* Another chunk ID (Int)
* Keyframe length/interval (Int) - Milliseconds
* Variable byte length (Short) - Probably encryption key information.
* Encryption key (Indicated length, string, encoded in some manner) - Required to decrypt chunk + keyframe data.

### Encryption Key
Is a variable length given in the data header (seems to be 32 bytes usually.) Base64 encode this in order to come up with some new key that is probably used.
