package actors;

import akka.actor.UntypedActor;
import akka.event.Logging;
import akka.event.LoggingAdapter;
import searchers.SearchSiteInfo;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.stream.Collectors;


public class ChildActor extends UntypedActor {
    LoggingAdapter log = Logging.getLogger(getContext().system(), this);
    SearchSiteInfo info;

    public ChildActor(SearchSiteInfo info) {
        this.info = info;
    }

    @Override
    public void onReceive(Object o) throws Throwable {
        if (o instanceof String)
        {
            String msg = (String) o;
            log.info("Send request '{}' into '{}' searching system via {} port", msg, info.desc, info.port);

            URI uri = URI.create(String.format("http://%s:%d/search?q=%s",
                                 info.host, info.port, msg));

            log.debug("URI: {}", uri.getQuery());

            HttpClient client = HttpClient.newBuilder().build();
            HttpRequest request = HttpRequest.newBuilder()
                    .uri(uri)
                    .build();

            String response = client
                                 .send(request, HttpResponse.BodyHandlers.ofString())
                                 .body().intern();

            sender().tell(new ChildActorResultMessage(response, info), getSelf());
        }
    }
}
