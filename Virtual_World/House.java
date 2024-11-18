import processing.core.PImage;

import java.util.List;

public class House extends Entity {
    public static final String HOUSE_KEY = "house";
    public static final int HOUSE_PARSE_PROPERTY_COUNT = 0;

    public House(String id, Point position, List<PImage> pImages) {
        super(id, position, pImages);
    }

}
