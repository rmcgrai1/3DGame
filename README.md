# 3DGame

The game is an open world adventure game inspired by MineCraft, The Legend of Zelda, and Skyrim. You can wander around, chop down trees, and battle enemies in sword-based combat. The game is still very early in development, but most of the basic elements are in place, such as image-loading, fonts and text-drawing, 3D graphics, shaders, and enemies.

##Setting up Git
sudo apt-get update

sudo apt-get install git

git config --global user.name "Username"

git config --global user.email "UserEmail"

ssh-keygen -t rsa -C "UserEmail"

eval "$(ssh-agent -s)"

ssh-add ~/.ssh/id_rsa

cat ~/.ssh/id_rsa.pub

####copy printed text to clipboard
####open github.com
####click on gear for "settings" in top right corner of screen
####click "ssh keys" on left side of page
####click "add SSH key" on right side
####create a title for this machine
####paste the text copied from ~/.ssh/id_rsa.pub in the "Key" box
####click "Add key" at the bottom of the "Key" box

ssh -T git@github.com

####type "yes" when the RSA fingerprint message appears
##Cloning GitHub Repository

git clone https://github.com/rmcgrai1/3DGame.git

cd 3DGame

## Installing Dependencies

sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) universe"

sudo apt-get update

sudo apt-get install g++

sudo apt-get install libX11-dev

sudo apt-get install libpng-dev

sudo apt-get install freeglut3-dev

sudo apt-get install libopenal-dev

sudo apt-get install libalut-dev

## Comments

The comments were made in Notepad++ on Windows, and do not always show up well in the terminal. If this is an issue, try opening up the file in Notepad++, where the formatting is sure to show up properly.

#Game Play 
####Intro Screen
On the intro Screen, a textbox will display a general introduction to the game. In order to close this box, press the 'u' key.

####Controls
- WASD keys: moving the player
- mouse cursor: aiming the sword
- left mouse button: swinging the sword 
- spacebar: jumping 

####Inventory
The inventory can be accessed with the 'i' button and exited out of with the same key. The inventory does not have anything that can be accessed 
at this time, but items can be moved by clicking them and then clicking a new inventory slot.

#Bugs:
- runs slowly over PuTTy, on computers without graphics cards
- character sinks through ground at certain seams
- inventory is sometimes dark
- character can walk through/fall through building
- smokerings make water invisible if they are in front of them
- smokerings are not always created when player is walking
- trees/shadows disappear too soon at edge
- randomly slows down tremendously
- enemies don't always see player
