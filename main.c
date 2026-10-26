#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int id;
    char title[100];
    char artist[100];
    struct Node *next;
} Node;

Node *CreateNode(int id, const char *title, const char *artist) {
    Node *newnode = malloc(sizeof(Node));
    if (newnode == NULL) return NULL;
    newnode->id = id;
    snprintf(newnode->title, sizeof(newnode->title), "%s", title);
    snprintf(newnode->artist, sizeof(newnode->artist), "%s", artist);
    newnode->next = NULL;
    return newnode;
}

Node *AddSong(Node *head, int id, const char *title, const char *artist) {
    Node *newnode = CreateNode(id, title, artist);
    if (newnode == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }
    if (head == NULL) return newnode;
    Node *curr = head;
    while (curr->next != NULL) curr = curr->next;
    curr->next = newnode;
    return head;
}

void DisplayList(Node *head) {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    Node *curr = head;
    while (curr != NULL) {
        printf("%d. %s - %s\n", curr->id, curr->title, curr->artist);
        curr = curr->next;
    }
}

Node *DeleteSong(Node *head, int id) {
    Node *curr = head;
    Node *prev = NULL;
    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("Song not found.\n");
        return head;
    }
    if (prev == NULL) head = curr->next;
    else prev->next = curr->next;
    printf("Deleted: %s\n", curr->title);
    free(curr);
    return head;
}

Node *ReverseList(Node *head) {
    Node *prev = NULL;
    Node *curr = head;
    Node *next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    printf("Reversed playlist:\n");
    DisplayList(prev);
    return prev;
}

Node *PlayNext(Node *head) {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return NULL;
    }
    Node *temp = head;
    printf("Now playing: %s - %s\n", temp->title, temp->artist);
    head = head->next;
    free(temp);
    return head;
}

void FreeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node *head = NULL;
    int choice, id, nextID = 1;
    char title[100], artist[100];

    while (1) {
        printf("\n--- MUSIC PLAYLIST ---\n");
        printf("1. Add song\n2. Display playlist\n3. Delete song\n");
        printf("4. Reverse playlist\n5. Play next song\n6. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }
        if (choice == 1) {
            printf("Song title: ");
            scanf(" %99[^\n]", title);
            printf("Artist: ");
            scanf(" %99[^\n]", artist);
            Node *newHead = AddSong(head, nextID, title, artist);
            if (newHead != head || head != NULL) {
                /* With a nonempty list, check whether the new ID was appended. */
                Node *curr = newHead;
                while (curr != NULL && curr->id != nextID) curr = curr->next;
                if (curr != NULL) nextID++;
            }
            head = newHead;
        } else if (choice == 2) {
            DisplayList(head);
        } else if (choice == 3) {
            printf("Song ID to delete: ");
            if (scanf("%d", &id) != 1) break;
            head = DeleteSong(head, id);
        } else if (choice == 4) {
            head = ReverseList(head);
        } else if (choice == 5) {
            head = PlayNext(head);
        } else if (choice == 6) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    FreeList(head);
    return 0;
}
