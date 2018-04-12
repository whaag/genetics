package net.my.item;

import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Item {
    private final int value;
    private final int weight;

    private Item(int value, int weight) {
        this.value = value;
        this.weight = weight;
    }

    public static Item randomItem() {
        final List<Item> items = Stream.of(new Item(10, 11), new Item(4, 8), new Item(5, 6)
                , new Item(2, 12), new Item(8, 5), new Item(2, 8), new Item(6, 4)
                , new Item(7,13)).collect(Collectors.toList());
        final int item = new Random().nextInt(items.size());
        return items.get(item);
    }

    public int getValue() {
        return value;
    }

    public int getWeight() {
        return weight;
    }
}