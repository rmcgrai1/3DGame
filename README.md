# 3DGame

The game is an open world that can be explored enemies can be fought and many things can happen

##set up git
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
##clone github repository

git clone https://github.com/rmcgrai1/3DGame.git

cd 3DGame

###install dependencies
sudo apt-get install g++##Not needed in last 2 tries, but required in first installation

sudo apt-get install libX11-dev##Not needed in first 2 tries, but needed last time

sudo apt-get install libpng-dev##Not needed in first 2 tries, but needed last time

sudo apt-get install freeglut3-dev

##OPENAL
sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) universe"

sudo apt-get update

sudo apt-get install libopenal-dev

sudo apt-get install libalut-dev

#Comments

The comments were made in Notepad++ on Windows, and do not always show up well in the terminal. If this is an issue, try opening up the file in Notepad++, where the formatting will show up properly.

#Game Play 
Intro Screen, in order to leave the intro is to press 'u' or the spacebar.

####Moving
the keys WASD will allow the player to move. The sword can be moved around with the mouse and clicking the mouse will allow the player to attack. 
The spacebar will allow the player to jump. 

####Inventory
The inventory can be accessed with the 'i' button and exited out of with the same key. The inventory does not have anything that can be accessed 
at this time but it can be seen and the items can be moved around from one part to another.

#Bugs:
- runs slowly over PuTTy, on computers without graphics cards
- character sinks through ground at certain seams
- character can walk through/fall through building
- smokerings make water invisible if they are in front of them
- smokerings are not always created when player is walking
- trees/shadows disappear too soon at edge
- randomly slows down tremendously
- enemies don't always see player