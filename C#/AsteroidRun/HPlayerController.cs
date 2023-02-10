using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;
using UnityEngine.UI;

public class HPlayerController : MonoBehaviour
    
{
    [SerializeField] private Text livesText = null;
    [SerializeField] private int numLives = 3;

    [SerializeField] private Text scoreField;

    private int score = 0;
    
    [SerializeField] private GameController hostGameController = null;
    
    [SerializeField] private float speed = 1.0f;
    
    // Refernce to the bullet game object we'll fire (null means no bullet, but we'll set this in Unity)
    [SerializeField] private GameObject bulletPrefab = null;
    
    // Time (in seconds) between bullet shots - the smaller the value the faster the fire rate.
    [SerializeField] private float fireDelayTime = 1.0f;
    
    private float fireTime = 0.0f;

    public void updateScore(int amount)
    {
        score += amount;

        scoreField.text = score.ToString();
    }

    // Start is called before the first frame update
    void Start()
    {
        livesText.text = numLives.ToString();
    }

    // Update is called once per frame
    void Update()
    {
        movePlayer();
        playerFire();
    }
    void movePlayer()
    {
        float leftRightInput = Input.GetAxis("Horizontal");
        float upDownInput = Input.GetAxis("Vertical");
        Vector2 horizontalMoveVector = Vector2.right * leftRightInput;
        Vector2 verticalMoveVector = Vector2.up * upDownInput;
        Vector2 moveVector = (horizontalMoveVector + verticalMoveVector) * speed * Time.deltaTime;
        transform.Translate(moveVector);
    }
    // Handle user input for fire
    void playerFire()
    {
        // Decrease fire countdown
        fireTime -= Time.deltaTime;

        // Only fire a bullet if we press the fire button (referred to input "Fire1" in the Unity Input Manager) AND our fire countdown has reached or passed 0 (remember this controls the fire rate)
        if (Input.GetButton("Fire1") && fireTime <= 0.0f)
        {
            // Use the bulletPrefab game object reference to create a new bullet at the player's position and orientation
            GameObject bullet = Instantiate(bulletPrefab, transform.position, transform.rotation);

            // The bullet game object will contain the SimpleBulletBehaviour component - get this and call the OwningPlayer property to set the owner of the bullet to the current player
            bullet.GetComponent<SimpleBulletBehaviour>().OwningPlayer = this;

            // Reset the fire countdown
            fireTime = fireDelayTime;
        }
    }
    void OnTriggerEnter2D(Collider2D collision)
    {
        // If we got hit, decrease the number of lives...
        numLives--;
        // ...and update the game HUD to reflect this
        livesText.text = numLives.ToString();

        // Remove the enemy laser game object from the scene
        Destroy(collision.gameObject);
        
    }
    public int numberOfLives()
    {
        return numLives;
    }
}
