using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// BossController is used to control the fire and collision properties of the boss invader.
// Note:  At runtime (when the game is running), a boss game object contains this component and either a LeftPath or RightPath component to control movement.
// Both components have an Update function and both Updates get called every frame, so spreading the update functionality of a game object
// across multiple components is fine.  Here we handle attacking and being hit, where LeftPath or RightPath handle movement.
public class BossController : MonoBehaviour
{
    // Reference a game object which models the laser the boss will fire (null means 'no laser at the moment' - we'll set this in Unity)
    [SerializeField] private GameObject laserPrefab = null;

    // fireDelayTime is the amout of time between the boss firing at us (Initialise to 1 seconds here, but we can change in Unity)
    [SerializeField] private float fireDelayTime = 1.0f;

    // fireTime is the actual countdown
    private float fireTime = 0.0f;

    // How many points do we get when we shoot the boss (with [SerializeField] we get to edit this in Unity too!)
    [SerializeField] private int pointsValue = 100;



    // Start is called before the first frame update
    void Start()
    {
        // Initialise out countdown 'fireTime' variable to the amount of time we wait between shots
        fireTime = fireDelayTime;
    }

    // Update is called once per frame
    void Update()
    {
        // This update only handles firing (see above comments) - call fireLaser to process this.
        // Note: Could put all the code in fireLaser here, but it keeps things organised and consistent - other scripts are organised this way too!
        fireLaser();
    }

    void fireLaser()
    {
        // Countdown - decrement our fireTime timer by the amount of time that has elapsed since the last frame.
        // Note:  Time.deltaTime is usually a very small number - something like 16 milliseconds - where a millisecond is one thousandth of a second)
        fireTime -= Time.deltaTime;

        // If out countdown reaches zero, we can fire!
        if (fireTime <= 0.0f)
        {
            // Create a new laser game object
            Instantiate(laserPrefab, transform.position, transform.rotation);

            // Do we have an audio component attached - if so play to sound!
            AudioSource audio = GetComponent<AudioSource>();
            if (audio)
            {
                audio.Play();
            }
           
            // Reset the timer back to the required delay time, so we wait however long until the next laser can be fired!
            fireTime = fireDelayTime;
        }
    }

    // Handle collision - the 'collision' parameter contains information about what other game object collided with the boss.
    void OnTriggerEnter2D(Collider2D collision)
    {
        // Different objects might collide with the boss - by assigning tags we can work out which object collided...
        // Here we're only interested in player bullets - everything else is okay :)
        if (collision.tag == "player_bullet")
        {
            // If you want to report what's happening - put a debug log call in - I've left this in to report which object hit the boss.
            Debug.Log(collision.tag);

            // This is a lengthy expression - let's break it down...
            // collision.gameObject gives us the main game object that hit the boss
            // .GetComponent<SimpleBulletBehaviour>() gets the bullet script we assigned to the bullet object
            // .OwningPlayer calls an accessor to return the player that fired the bullet
            // .updateScore passed the boss's points value to update the player's score
            collision.gameObject.GetComponent<SimpleBulletBehaviour>().OwningPlayer.updateScore(pointsValue);

            // On hit, remove the boss from the scene
            Destroy(gameObject);

            // The bullet should go too, so remove this from the scene as well.
            Destroy(collision.gameObject);
        }

    }

    // A simple accessor method to return to the caller the points value of the boss.
    // Note: It seems like more work to store pointsValue as private and have this function to return it directly.  But accessor methods like this are the gate-keepers to the data (pointsValue in this case) and ensure invalid data cannot be stored.
    public int getPointsValue()
    {
        return pointsValue;
    }

}
