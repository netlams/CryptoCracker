# CryptoCracker
<p>For Computer Sys. and Low-Level Programming class</p>

<h2>Language written in:</h2>
<p>C</p>

<h2>Compilation Platform:</h2>
<p>Linux / MAC OS X </p>

<h2>Description:</h2>
<p>In this project, the goal is to decrypt a text file encypted with a shift cipher.
A shift cipher is a basic cryptographic algorithm in which encryption is performed by substituting each
character in the plaintext with the character that's a fixed number of characters (i.e. the shift value) later in the alphabet. For example, if our shift value is 2, the plaintext cabbage becomes ecddcig. </p>

<h2>Usage:</h2>
<p>The name of the file to crack is passed as a command-line argument. (Optionally) on the same command-line, you may include a dictionay-word-list file, or else it will read the default words file. The program will determine the proper shift value, and then output the decrypted text.</p>

<h2>Testing:</h2>
<p>To Test, please run/compile crypto_main.c
And enter jaws_encr.txt or an encrypted text file into the command-line. You may optionally enter a dict file. If not it will look at the default path. 
Wait a few minutes (decrypting) and it will output the decrypt text. </p>
<img src="https://github.com/netlams/CryptoCracker/blob/master/TestScreens/begin.png" />
