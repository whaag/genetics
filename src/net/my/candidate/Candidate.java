package net.my.candidate;

import net.my.item.Item;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Candidate {
    private List<Item> items;

    private Candidate() {
        items = new ArrayList<>();
    }

    public static Candidate generateCandidate() {
        Candidate candidate = new Candidate();

        while (candidate.items.size() == 0 || candidate.getTotalWeight() > 15) {
            candidate = new Candidate();
            final int numberOfItems = new Random().nextInt(8) + 1;
            for (int i = 0; i < numberOfItems; i++) {
                candidate.addToItems(Item.randomItem());
            }
        }

        return candidate;
    }

    public void addToItems(final Item item) {
        items.add(item);
    }

    public Item popItem() {
        final int index = new Random().nextInt(items.size());
        return items.remove(index);
    }

    public int getTotalValue() {
        return items.stream()
                .mapToInt(Item::getValue)
                .sum();
    }

    public int getTotalWeight() {
        return items.stream()
                .mapToInt(Item::getWeight)
                .sum();
    }

    public List<Item> getItems() {
        return items;
    }
}
