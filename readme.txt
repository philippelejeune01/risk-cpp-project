GameEngine's Map and Player vectors are now declared static so they can be used in PlayerStrategyies for
orders such as Advance and Negotiate.

Added int doesOwn(string name) to class Player which returns the index of the territory if found or -1 if not.

Added removeCard(int index) to class Hand to remove the card played from the player's pool.

Changed a bunch of variables that are declared to pointer type.

Implemented HumanPlayerStrategy.
