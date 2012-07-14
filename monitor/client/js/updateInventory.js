/**
 * @author sylvia_r
 * 
 */

function update_inventory() {
	
	if (inventoryOpenId != -1 && !cache.playerExist(inventoryOpenId))
		closeInventory();
	else if (inventoryOpenId != -1 && cache.getPlayer(inventoryOpenId).inventoryChange_)
		updateInventoryContent(cache.getPlayer(inventoryOpenId).inventory_, cache.getPlayer(inventoryOpenId).lastInventory_);
}

function setAllInventoryChange(players, v) {
	
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
		if (cache.playerExist(prev[i].id_) && inventoryOpenId == prev[i].id_)
			{
				now = cache.getPlayer(prev[i].id_);
				if (!sameInventory(prev[i].inventory_, now.inventory_))
					cache.setInventoryChange(prev[i].id_, true, prev[i].inventory_);
			}
	}
}
