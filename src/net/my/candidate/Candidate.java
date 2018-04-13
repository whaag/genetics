package net.my.candidate;

import net.my.item.Item;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Candidate {
    private List<Boolean> items;

    public Candidate() {
        items = new ArrayList<>();
    }

    public static Candidate generateCandidate() {
        Candidate candidate = new Candidate();

        while (candidate.items.size() == 0 || candidate.getTotalWeight() > 15) {
            candidate = new Candidate();
            for (int i = 0; i < 8; i++) {
                candidate.items.add(i, new Random().nextBoolean());
            }
        }

        return candidate;
    }

}
