using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

// HPlayerController implements the functionality for a horizontally moving player (like the player in space invaders!)
public class HPlayerController : MonoBehaviour
{
    // Reference to the main game controller
    [SerializeField] private GameController gameController = null;

    // Input "axis" to read - abstraction of keyboard / joystick - we store the name used by Unity's Input Manager
    [SerializeField] private string moveInput = "Horizontal";

    // How much to move per-second
    [SerializeField] private float moveSpeed = 1.0f;

    // Refernce to the bullet game object we'll fire (null means no bullet, but we'll set this in Unity)
    [SerializeField] private GameObject bulletPrefab = null;
    // Time (in seconds) between bullet shots - the smaller the value the faster the fire rate.
    [SerializeField] private float fireDelayTime = 1.0f;

    // Actual countdown value to when we can fire next (start at 0 so we can fire immediately)
    private float fireTime = 0.0f;

    // Numer of lives and reference to text field to show the number of lives in the game HUD (uses Unity UI)
    // Can set both in Unity
    [SerializeField] private Text livesText = null;
    [SerializeField] private int numLives = 3;

    
    // Current score and reference to score field in the game HUD (uses Unity UI)
    [SerializeField] private Text scoreText = null;

    // Note: unlike lives, there's no point in setting score in Unity since it starts at 0 (so no [SerializeField] attribute here)
    private int score = 0;


    // Start is called before the first frame update
    void Start()
    {
        // Set the game HUD to current score and lives
        scoreText.text = score.ToString();
        livesText.text = numLives.ToString();
    }

    // Update is called once per frame
    void Update()
    {
        // Two things to do - move player and handle fire
        // We've done divide and conquer here - move and fire in separate functions to help manage complexity!
        playerMove();
        playerFire();
    }

    // Handle user input for movement
    void playerMove()
    {
        // Read the moveInput axis (the string defauled to "Horizontal" above) - this will be -1, 0 or 1 for a keypress and anywhere inbetween for an analogue input like a joystick.
        float delta = Input.GetAxis(moveInput);

        // Move (Translate) the player accordingly) - negative delta means left movement, and we ALWAYS factor in time!
        transform.Translate(Vector2.right * delta * moveSpeed * Time.deltaTime);
    }

    // Handle user input for fire
    void playerFire()
    {
        // Decrease fire countdown
        fireTime -= Time.deltaTime;

        // Only fire a bullet if we press the fire button (referred to input "Fire1" in the Unity Input Manager) AND our fire countdown has reached or passed 0 (remember this controls the fire rate)
        if (Input.GetKeyDown("space") && fireTime <= 0.0f)
        {
            // Use the bulletPrefab game object reference to create a new bullet at the player's position and orientation
            GameObject bullet = Instantiate(bulletPrefab, transform.position, transform.rotation);

            // The bullet game object will contain the SimpleBulletBehaviour component - get this and call the OwningPlayer property to set the owner of the bullet to the current player
            bullet.GetComponent<SimpleBulletBehaviour>().OwningPlayer = this;

            // Get the audio source attached to the player and play the fire sound.
            AudioSource audio = GetComponent<AudioSource>();
            if (audio)
            {
                audio.Play();
            }

            // Reset the fire countdown
            fireTime = fireDelayTime;
        }
    }

    // Handle collision - the 'collision' parameter contains information about what other game object collided with the player.
    void OnTriggerEnter2D(Collider2D collision)
    {
        // Different objects might collide with the player - by assigning tags we can work out which object collided...
        // Here we're only interested in enemy lasers - everything else is okay :)
        if (collision.tag == "enemy_laser")
        {
            // If we got hit, decrease the number of lives...
            numLives--;
            // ...and update the game HUD to reflect this
            livesText.text = numLives.ToString();

            // Remove the enemy laser game object from the scene
            Destroy(collision.gameObject);

            // Note: The player handles player-related things - not over-arching game elements like managing end of game etc - 
            // We don't check for lives = 0 here (ie. game over), the game controller goes this (and uses the numberOfLives function to find out how many lives are left - see below)
        }
    }

    // Accessor function to return the number of lives left
    public int numberOfLives()
    {
        return numLives;
    }

    // Function to update the players score based on the provided number of points.
    public void updateScore(int points)
    {
        // Increase the score variable
        score += points;

        if (scoreText)
        {
            // Update the game HUD to reflect the new value
            scoreText.text = score.ToString();
        }
    }
}
