package seachers;

import org.mockserver.integration.ClientAndServer;
import scala.concurrent.duration.Duration;

import java.util.stream.Collectors;
import java.util.stream.IntStream;

import static org.mockserver.integration.ClientAndServer.startClientAndServer;
import static org.mockserver.model.HttpRequest.request;
import static org.mockserver.model.HttpResponse.response;
import static org.mockserver.model.HttpStatusCode.OK_200;

public class SearcherStubServer implements AutoCloseable {
    private final ClientAndServer stubServer;

    SearcherStubServer(int port, Duration timeout)
    {
        stubServer = startClientAndServer(port);
        stubServer.when(request()
                .withMethod("GET")
                .withPath("/search")
        ).respond(
                request -> {
                    if (timeout.toMillis() > 0)
                        Thread.sleep(timeout.toMillis());

                    String name = request.getFirstQueryStringParameter("q");

                    return response()
                            .withStatusCode(OK_200.code())
                            .withBody(genResponse(name));
            }
        );
    }

    static public String genResponse(String name)
    {
        return IntStream.range(1, 5).
                mapToObj(i -> name + " " + i).
                collect(Collectors.joining("\n"));
    }

    @Override
    public void close() throws Exception {
        stubServer.close();
    }
}
