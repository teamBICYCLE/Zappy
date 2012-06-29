/**
 * @author sylvia_r
 * 
 */

function update_inventory() {
	
	if (inventoryOpenId != -1 && !cache.playerExist(inventoryOpenId))
		closeInventory();
	else if (inventoryOpenId != -1)
	{
		console.log("Update inventory player #" + inventoryOpenId);
	}
	// else
		// console.log("no update inventory");
}
