using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameController : MonoBehaviour
{

    [Header("Object References")]

    public Transform wall;
    public Transform player;
    public Transform orb;
    public Transform goal;
    public Transform background;

    private ParticleSystem goalPS;

    public Text scoreText;

    public AudioSource goalAppear;
    public AudioSource orbcollected;


    public static GameController _instance;
    private int orbsCollected;
    private int orbsTotal;

    private int[][] level = new int[][]
    {
        /* 1 = Wall
         * 2 = player
         * 3 = orb
         * 4 = goal
         */
        new int[] {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
        new int[] {1,0,0,0,0,0,3,0,0,0,0,0,0,0,0,1,1,1,1},
        new int[] {1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        new int[] {1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
        new int[] {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        new int[] {1,1,1,1,1,1,1,0,0,0,3,0,0,0,0,0,0,0,1},
        new int[] {1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
        new int[] {1,0,0,0,0,0,0,3,0,0,0,0,0,0,1,1,1,1,1},
        new int[] {1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1},
        new int[] {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
        new int[] {1,0,0,3,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1},
        new int[] {1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1},
        new int[] {1,0,0,2,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1},
        new int[] {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

   
   
    void BuildLevel()
    {
        GameObject dynamicParent = GameObject.Find("Dynamic Objects");
        for (int yPos = 0; yPos < level.Length; yPos++)
        {
            for (int xPos = 0; xPos < (level[yPos]).Length; xPos++)
            {
                Transform toCreate = null;
                switch(level [yPos] [xPos])
                {
                    case 0:
                        break;

                    case 1:
                        toCreate = wall;
                        break;

                    case 2:
                        toCreate = player;
                        break;

                    case 3:
                        toCreate = orb;
                        break;

                    case 4:
                        toCreate = goal;
                        break;

                    case 5:
                        toCreate = background;
                        break;

                    default:
                        print("Invalid number: " + (level[yPos][xPos].ToString()));
                        break;



                }

                if(toCreate != null)
                {
                    Transform newObject = Instantiate(toCreate, new Vector3(xPos, (level.Length - yPos), 0), toCreate.rotation) as Transform;

                    if (toCreate == goal)
                    {
                        goalPS = newObject.gameObject.GetComponent<ParticleSystem>();
                    }

                    newObject.parent = dynamicParent.transform;

                  

                }
            }
        }
    }

    void Start()
    {
        BuildLevel();
        GameObject[] orbs;
        orbs = GameObject.FindGameObjectsWithTag("Orb");

        orbsCollected = 0;
        orbsTotal = orbs.Length;

        scoreText.text = "Orbs Collected: " + orbsCollected + "/" + orbsTotal;
       
    }
    public void playCollectSound()
    {
        orbcollected.Play();

    }
    void Awake()
    {
        _instance = this;
        
    }

    public void CollectedOrb()
    {
        orbsCollected++;
        scoreText.text = "Orbs Collected: " + orbsCollected + "/" + orbsTotal;

        if(orbsCollected >= orbsTotal)
        {
            goalPS.Play();
            goalAppear.Play();
        }
    }

}
