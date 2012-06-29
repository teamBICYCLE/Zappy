/**
 * @author sylvia_r
 * 
 */

function update_inventory() {
	
	if (cache.getPlayers().length > 0)
	{
		console.log(inventoryOpenId);
		if (inventoryOpenId != -1 && !cache.playerExist(inventoryOpenId))
			closeInventory();
		else if (inventoryOpenId != -1 && cache.getPlayer(inventoryOpenId).inventoryChange_ ||
				inventoryOpenId != lastInventoryOpenId)
		{
			console.log(cache.getPlayer(inventoryOpenId).inventoryChange_);
			cache.getPlayer(inventoryOpenId).inventoryChange_ = false;
			//console.log(cache.getPlayer(inventoryOpenId));
			console.log("Update inventory player #" + inventoryOpenId);
			//updateInventoryContent([5, 2, 0, 0, 0, 0, 0]);
		}
		// else
			// console.log("no update inventory");
	}
}

function setInventoryChange(players, v) {
	
	for (var i = 0; i != players.length; i++)
		players[i].inventoryChange_ = v;
	return players;
}

function sameInventory(player1, player2) {
	for (var i = 0; i != player1.length; i++)
		if (player1[i] != player2[i])
			return false;
	return true;
}

function detectInventoryChange(prev) {
	
	var now;
	for (var i = 0; i != prev.length; i++)
	{
		//console.log(prev[i].id_);
		if (cache.playerExist(prev[i].id_) && inventoryOpenId == prev[i].id_)
			{
				now = cache.getPlayer(prev[i].id_);
				if (sameInventory(prev[i].inventory_, now.inventory_))
				{
					cache.setInventoryChange(prev[i].id_, false);
					//now.inventoryChange_ = true;
				}
			}
	}
}
