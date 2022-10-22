#############################
# Naive build script for A02
# Author: Mahmoud Hamdy
#############################

# Variables
MY_UTILS = mypwd myecho mycp mymv

# Recipes

# Build all utilities
# Run using: make or make all
.PHONY: all
all: $(MY_UTILS)

# Build any utility
# Run using: make your_utility (Hint: same name as utility.c)
# Examply: make mypwd ---> (Same name as mypwd.c)
%: %.c
	gcc -Wall $< -o $@

# Delete all utilities
# Run using: make clean
.PHONY: clean
clean:
	rm -f $(MY_UTILS)

