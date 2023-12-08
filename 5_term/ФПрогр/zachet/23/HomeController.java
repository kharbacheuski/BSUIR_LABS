package controllers
import play.mvc.*;

public class HomeController extends Controller {

    public String index() {
        return "Hello world";
    }
}