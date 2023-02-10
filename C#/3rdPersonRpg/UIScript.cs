using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class UIScript : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    // functions to switch between scenes to showcase everyones work

    public void Back()
    {
        SceneManager.LoadScene("ChoosePrototype");
    }
    public void NextScene()
    {
        SceneManager.LoadScene("ChoosePrototype");
    }

    public void Kyle()
    {
        SceneManager.LoadScene("weather");
    }

    public void Dylan()
    {
        SceneManager.LoadScene("Player");
    }

    public void Harry()
    {
        SceneManager.LoadScene("Wallrunning");
    }

    public void Eessa()
    {
        SceneManager.LoadScene("Player 1");
    }

    public void James()
    {
        SceneManager.LoadScene("Real Desert");
    }
}
