<img src="/Microsoft-Defender.jpg"
    title="Simple-MSD-Evador" align="left" height=75 length=75 />

# Simple-MSD-Evador
A shellcode Loader designated to avoid Microsoft Defender.

Nothing too fancy, just a simple tool uses AES from CrytoPP to encrypt and obvisacate the shellcode to avoid static engines of EDRs and MSD.

## Usage:
1.Make sure Visual Studio, MSBuild and cryptopp are available. Also, cryptopp has to be recognzed by Visual Studio.

2.Run the program with the path of the shellcode as an argument.

3.Save encrypted payload output.

4.Change the payload in the designated area.

5.Run with no arguments.

