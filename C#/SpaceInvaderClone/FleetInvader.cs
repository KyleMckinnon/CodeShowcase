using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// FleetInvader is a variation of the Enemy component, but is not intended to work alone - a host fleet game object looks after a collection of FleetInvaders and coordinates their actions...
public class FleetInvader : MonoBehaviour
{
    // A private reference to the fleet 
    private InvaderFleetController hostFleet = null;

    // How many points we get for shooting the invader - we can edit this in Unity too.
    [SerializeField] private int pointsValue = 10;

    [SerializeField] private Animator animator = null;

    // Handle collision - the 'collision' parameter contains information about what other game object collided with the invader.
    void OnTriggerEnter2D(Collider2D collision)
    {
        // Different objects might collide with the invader - by assigning tags we can work out which object collided...
        // Here we're only interested in player bullets - everything else is okay :)
        // So, if the invader is part of a fleet and a player bullet hit...
        if (hostFleet && collision.tag=="player_bullet")
        {
            if (animator)
            {
                animator.SetBool("isAlive", false);
            }
            

                // Remove the bullet - we don't want super bullets that pass through invaders without stopping - would be nice though :)
                Destroy(collision.gameObject);
        }

    }

    public void destroyInvader()
    {
        // Tell the fleet the invader got hit - the invader knows, but the fleet needs to know too.
        hostFleet.invaderDestroyed(this);

        // Remove the invader
        Destroy(gameObject);
    }

    // Set the hostFleet reference about so the given FleetInvader becomes part of the fleet.
    public void assignToFleet(InvaderFleetController fleet)
    {
        hostFleet = fleet;
    }

    // In FleetInvader, we don't move in the Update function as we did for Enemy - the fleet will call this and tell the invader by how much to move...
    public void moveInFleet(float dx, float dy)
    {
        // Move across (according to dx - when dx is negative we move left) and vertically
        // Note:  Adding vectors this way is common when moving game objects - we call it a linear combination (you'll see this again when studying graphics!)
        transform.Translate(Vector2.right * dx + Vector2.up * dy);
    }

    // In FleetInvader, we also don't control firing directly - the fleet will call this to instruct an invader to fire when needed...
    public void fire(GameObject prefab)
    {
        // When the invader fires, create a new laser game object
        Instantiate(prefab, transform.position, transform.rotation);
    }

    // Accessor method that tells the caller how many points we get for shooting the invader.
    public int getPointsValue()
    {
        return pointsValue;
    }
}
