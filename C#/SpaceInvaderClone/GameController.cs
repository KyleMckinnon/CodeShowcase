using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

// The game controller component will be part of a game controller game object (surprise surprise) in our Unity scene.
// It doesn't appear anywhere, but works "invisibly" every frame looking after so-called global properties like when you lose or win a level, something other game objects shouldn't need to worry about.
public class GameController : MonoBehaviour
{
    // Reference to the main player - we'll set in Unity
    [SerializeField] private HPlayerController player = null;

    // Reference to the enemy fleet - we'll set in Unity
    [SerializeField] private InvaderFleetController fleet = null;
    
    // Track which level we're on - we start counting internally from 0 but we present level 1 to the player!
    // Note:  Counting in code starts from 0, useful when accessing collections of objects, so this is a convinient value to start from.  When presenting the current level to the player we just show the value 'currentLevel + 1'.  We could say currentLevel = 1 if we want, and -1 when accessing collections.  It's up to you, but I've written these components around currentLevel starting at 0.
    private int currentLevel = 0;


    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        // If the player has run out of lives, load scene to show you lost!
        if (player.numberOfLives()==0)
        {
            // Game Over
            //SceneManager.LoadScene("GameOver-Lose");
            SceneManager.LoadScene("GameOver");
        }
        else if (fleet.numberOfInvaders()==0)
        {
            // Otherwise if the fleet has lost all it's invaders we go to the next level...
            currentLevel++;

            // If we reach the last level we load the "you win" scene...
            if (currentLevel > 1)
            {
                SceneManager.LoadScene("WinScreen");
            }
            else
            {
                // ...otherwise ask the fleet to regenerate the next set of invaders
                fleet.generateFleet(currentLevel);
            }
        }
    }

    // When an invader get's hit, it the game controller gets told how many points to award which in turn tells the player to add the points.
    // Note: Here we're calling functions on different game objects - like stepping stones, we pass points from invader (which stores the points value for a hit) through fleet, to the game controller (this function) and eventually to player.  Why do this?  Well, each game object should store and process data only relevant to itself.  This means data is split across multiple game objects, and we often need to pass it around to get it to where it needs to be.  In this case the points to award is passed from invader to player.
    public void updatePlayerScore(int points)
    {
        if (player)
        {
            player.updateScore(points);
        }
    }

    // Accessor method to return the current leve we're on.  
    public int getCurrentLevel()
    {
        return currentLevel;
    }
}
