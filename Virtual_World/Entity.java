import processing.core.PImage;

import java.util.List;

/** Represents an entity that exists in the virtual world. */
public abstract class Entity {

    public static final int ENTITY_PROPERTY_KEY_INDEX = 0;
    public static final int ENTITY_PROPERTY_ID_INDEX = 1;
    public static final int ENTITY_PROPERTY_POSITION_X_INDEX = 2;
    public static final int ENTITY_PROPERTY_POSITION_Y_INDEX = 3;
    public static final int ENTITY_PROPERTY_COLUMN_COUNT = 4;


    /** Entity's identifier that often includes the corresponding 'key' constant. */
    private String id;

    /** Entity's x/y position in the world. */
    private Point position;

    /** Entity's inanimate (singular) or animation (multiple) images. */
    private List<PImage> images;

    /** Index of the element from 'images' used to draw the entity. */
    private int imageIndex;


    public Entity( String id, Point position, List<PImage> images) {
        this.id = id;
        this.position = position;
        this.images = images;
        this.imageIndex = 0;
    }

    /** Helper method for testing. Preserve this functionality for all kinds of entities. */
    public String log(){
        if (id.isEmpty()) {
            return null;
        } else {
            return String.format("%s %d %d %d", id, position.x, position.y, imageIndex);
        }
    }

    /** Called when an animation action occurs. */
    public void updateImage(){}

    /** Called to begin animation and/or behavior for an entity. */

    public String getId(){
        return id;
    }

    public int getImageIndex() {
        return imageIndex;
    }

    public void setImageIndex(int imageIndex){
        this.imageIndex = imageIndex;
    }

    public List<PImage> getImages() {
        return images;
    }

    public Point getPosition() {
        return position;
    }

    public void setPosition(Point position) {
        this.position = position;
    }

}
