using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameController : MonoBehaviour
{
    [SerializeField] private HPlayerController player = null;

    public void updatePlayerScore(int amount)
    {
        player.updateScore(amount);
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }


    // Update is called once per frame
    void Update()
    {
        if (player.numberOfLives() == 0)
        {
            // Game Over
            //SceneManager.LoadScene("GameOver-Lose");
            SceneManager.LoadScene("GamePlay");
        }
    }
}
